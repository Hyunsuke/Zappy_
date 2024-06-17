#!/usr/bin/env python3

from sys import stdout
import sys
import re
import socket
from InventoryManager import InventoryManager
import threading
import os


class Command:
    def __init__(self, socket, current_inventory, team_name):
        self.status = -1
        self.player_ready = 0
        self.elevation = False
        self.team_name = team_name
        self.socket = socket
        self.current_inventory = current_inventory
        self.level = 1
        self.data_received = ""
        self.commandWaitingRoom = 0
        self.dataIndex = 0
        self.debug = 0
        self.lookString = ""
        self.shallMove = False
        self.positionHasBeenChanged = False
        self.forwardIndex = 0
        self.isLookUpdated = False
        self.inventoryString = ""
        self.isInventoryUpdated = False
        self.hasElevated = False
        self.commandList = []
        self.responseList = []
        self.leaderIsChosen = -1 # -1 signifie qu'il n'y a pas encore de leader attribué, 0 si c'est quelqu'un d'autre le leader, 1 si c'est moi
        # Il faut aussi que lorsque le leader est chosen il envoi en boucle son message et dans cette fonciton il faut mettre leaderIsChosen == 0
        thread_reception = threading.Thread(target=self.reception_loop)
        thread_reception.start()
        # thread_send = threading.Thread(target=self.sendArrayCmd)
        # thread_send.start()

    def sendArrayCmd(self):
            # print("len : ", len(self.commandList))
        while len(self.commandList) != 0:
            try:
                if (self.commandWaitingRoom < 10):
                    if (len(self.commandList) != 0):
                        self.socket.sendall(f"{self.commandList[0]}\n".encode())
                        self.commandList.pop(0)
                        self.commandWaitingRoom += 1
            except socket.error as e:
                print(f"Error sending command '{self.commandList[0]}': {e}")
                # return None
                os._exit(84)

    def getWaitingRoom(self):
        return self.commandWaitingRoom

    def send_command(self, command):
        self.commandList.append(command)
        self.responseList.append(command)

    def getResponseArray(self):
        data = self.socket.recv(1024).decode().strip()
        data_array = data.split('\n')
        return data_array

    def processResponseArray(self, data):
        self.data_received = data
        if self.elevation == True:
            print("Data received : ", self.data_received)
            self.elevation = False
            return
        if data == "Elevation underway" and self.level >= 2 and self.leaderIsChosen != 1:
            self.elevation = True
            return
        if data == "dead":
            print("Dead then exit")
            os._exit(0)
        if not data:
            # Gérer la déconnexion ou la fin de la communication
            print("Déconnexion du serveur")
            os._exit(0)
        if data.startswith("message"):
            print("Le recv reçu est un broadcast")
            self.adjustBroadcast()
        else:
            # print("Données > " + data)
            # print("We received " + data)
            # print("for command" + self.responseList[0])
            self.adjustData()
            if not self.responseList:
                return
            if (self.responseList[0] == "Incantation" and self.data_received == "ok"):
                pass
            else:
                self.commandWaitingRoom -= 1 # C'est parce que Incantation est la seule commande à envoyer 2 recv
            # else:
            #     if self.data_received == "ko":
            #         self.commandWaitingRoom -= 1
            self.responseList.pop(0)

    def reception_loop(self):
        while True:
            try:
                data_array = self.getResponseArray()
                for element in data_array:
                    self.processResponseArray(element)

            except socket.error as e:
                print(f"Erreur lors de la réception des données : {e}")
                os._exit(0)

    def adjustData(self):
        if not self.responseList:
            return
        if self.responseList[0].startswith("Take"):
            # print("C'est la réponse du Take")
            self.adjustTake()
        elif self.responseList[0].startswith("Set"):
            # print("C'est la réponse du Set")
            self.adjustSet()
        elif self.responseList[0].startswith("Incantation"):
            # print("C'est la réponse du Incantation")
            self.adjustIncantation()
        elif self.responseList[0].startswith("Eject"):
            # print("C'est la réponse du Eject")
            self.adjustEject()
        elif self.responseList[0].startswith("Broadcast"):
            if self.responseList[0].endswith("END"):
                if self.leaderIsChosen == -1:
                    self.leaderIsChosen = 1
                    self.status = -2
        elif self.responseList[0].startswith("Forward"):
            self.adjustForward()
        elif self.responseList[0].startswith("Current level"):
            if self.data_received != "ko":
                self.level += 1
                self.hasElevated = True
                print("Data received : ", self.data_received)
        if self.responseList[0].startswith("Look"):
            self.lookString = self.data_received
            self.isLookUpdated = True
        if self.responseList[0].startswith("Inventory"):
            self.inventoryString = self.data_received
            self.isInventoryUpdated = True

    def positionChanged(self):
        return self.positionHasBeenChanged

    def adjustForward(self):
        # if self.nb != 0 il faut continuer la fonction
        if self.leaderIsChosen == -1:
            return
        if self.positionHasBeenChanged == True:
            return
        if self.status == 0:
            return
        if self.status == 1 or self.status == 3 or self.status == 5 or self.status == 7:
            # print("CHANGE POSITION")
            self.positionHasBeenChanged = True
        else:
            self.forwardIndex += 1
            if self.forwardIndex == 2:
                # print("CHANGED POSITION TO CORNER")
                self.positionHasBeenChanged = True
                self.forwardIndex = 0
            # else:
            #     print("Forward Index: ", self.forwardIndex)

    def adjustBroadcast(self):
        # print("Données reçu : " + self.data_received)
        broadcastMessage = self.skip_to_first_comma(self.data_received)
        num = self.recuperer_chiffre(self.data_received)
        # print(num)
        # print(broadcastMessage)
        team_name, object, fct = self.getBroadcastMessage(broadcastMessage)
        print("Name : " + team_name + " object : " + object + " fct : " + fct + " num : " + str(num))
        if team_name == self.team_name:
            if fct == "Take":
                if object in self.current_inventory.shared_inventory:
                    self.current_inventory.shared_inventory[object] += 1
                    # Check si current inventory + shared inventory >= objective inventory
                    self.validateInventory(object)
            elif fct == "OK":
                if object in self.current_inventory.shared_inventory:
                    print("Il faut pop l'objet du objective inventory")
                    # self.pop_item(object)
                    self.validateInventory(object, True)
                    # Check si on a atteint l'objectif
            elif fct == "END":
                if self.leaderIsChosen != -1:
                    return
                self.leaderIsChosen = 0 # 0 si c'est quelqu'un d'autre le leader, 1 si c'est moi
                # if self.positionHasBeenChanged == True:
                #     if self.shallMove == False:
                #         # print("Je devrais bouger vers le numéro : ", num)
                #         self.status = num
                #         self.shallMove = True
                # else:
                #     print("Je ne bouge pas, j'attends la réponse de la commande : ", self.status)
                # Prendre les coordonées du boug
                print("Je vais rejoindre l'émetteur du message")
                # os._exit(0) # A supprimer
                # On a trouvé tous les items, il faut passer lvl8
            elif fct == "SET":
                # Check si l'appel au lvl 8 a été fait pour savoir si on fait la fonction ou pas
                # if object in self.current_inventory.shared_inventory:
                #     self.current_inventory.shared_inventory[object] -= 1
                return
            elif fct == "ready" and self.leaderIsChosen == 1:
                self.player_ready += 1
                if self.player_ready == 5:
                    print("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||")
                return
            elif fct == "come":
                if self.positionHasBeenChanged == True:
                    if self.shallMove == False:
                        # print("Je devrais bouger vers le numéro : ", num)
                        self.status = num
                        self.shallMove = True
                # else:
                #     print("Je ne bouge pas, j'attends la réponse de la commande : ", self.status)

    def elevate(self):
        return self.hasElevated

    def shouldMove(self):
        return self.shallMove

    def skip_to_first_comma(self, string):
        pos = string.find(',')
        if pos != -1:
            return string[pos + 2:]  # Récupère la sous-chaîne après la première virgule et l'espace
        else:
            # Si aucune virgule n'est trouvée, retourne la chaîne originale
            return string

    def recuperer_chiffre(self, text):
        matches = re.findall(r'\b\w\b', text)
        return int(matches[0])

    def adjustEject(self):
        return

    def adjustIncantation(self):
        # Le booléen de l'incantation doit être mis sur false
        if self.data_received == "ko":
            self.responseList.pop(1)
            return
        # os._exit(0)

    def adjustSet(self):
        # Baisser le shared inventory de 1
        response = self.responseList[0].split(' ')
        objectTaken = response[1]
        if self.data_received == "ko":
            return
        if self.level == 1:
            return

    def validateInventory(self, objectTaken, broadcast=False):
        if self.check_inventory() == True:
            print("Tous les items ont été trouvés. Go faire le passage lvl8")
            self.broadcastMaterial(objectTaken, "END")
            # self.pop_item(objectTaken)
            # self.status = -3
            return True
        if self.check_item(objectTaken) == True:
            if broadcast == False and objectTaken != "food":
                self.broadcastMaterial(objectTaken, "OK")
            # self.pop_item(objectTaken)
            return True
        return False

    def adjustTake(self):
        # Augmenter le shared inventory de 1
        # cmd, object = self.responseList[0]
        response = self.responseList[0].split(' ')
        objectTaken = response[1]
        # Check si c'est ok
        if self.data_received == "ko":
            return
        if self.level == 1:
            return
        if self.validateInventory(objectTaken) == True:
            return
        self.broadcastMaterial(objectTaken, "Take")

    def move_forward(self, needPrint=False):
        self.send_command("Forward")
        if needPrint:
            print("Move forward")

    def turn_right(self, needPrint=False):
        self.send_command("Right")
        if needPrint:
            print("Turn right")

    def turn_left(self, needPrint=False):
        self.send_command("Left")
        if needPrint:
            print("Turn left")

    def look(self, needPrint=False):
        self.send_command("Look")
        if needPrint:
            print("Look : ")

    def inventory(self, needPrint=False):
        self.send_command("Inventory")
        if needPrint:
            print("Inventory : ")

    def broadcast(self, message):
        return self.send_command(f"Broadcast {message}")

    def connect_nbr(self, needPrint=False):
        self.send_command("Connect_nbr")
        if needPrint:
            print("Connect_nbr : ")

    def fork(self, needPrint=False):
        self.send_command("Fork")
        if needPrint:
            print("Fork : ")

    def eject(self, needPrint=False):
        self.send_command("Eject")
        if needPrint:
            print("Eject : ")

    def take_object(self, object):
        print("Take object : " + object)
        self.send_command("Take " + object)

    def set_object_down(self, object):
        # print("Set object : " + object)
        self.send_command("Set " + object)

    def incantation(self, needPrint=False):
        self.send_command("Incantation")
        if needPrint:
            print("Incantation : ")

    def getBroadcastMessage(self, response):
        parts = response.split('_')
        if len(parts) != 3:
            raise ValueError("La chaîne d'entrée n'est pas au format 'teamname_object_fct'")
        # On récupère le nom de l'équipe et l'objet
        team_name = parts[0]
        object_name = parts[1]
        fct = parts[2]
        return team_name, object_name, fct

    def broadcastMaterial(self, material, fct):
        if (material == "linemate"):
            return self.broadcast(f"{self.team_name}_linemate_{fct}")
        elif (material == "deraumere"):
            return self.broadcast(f"{self.team_name}_deraumere_{fct}")
        elif (material == "sibur"):
            return self.broadcast(f"{self.team_name}_sibur_{fct}")
        elif (material == "mendiane"):
            return self.broadcast(f"{self.team_name}_mendiane_{fct}")
        elif (material == "phiras"):
            return self.broadcast(f"{self.team_name}_phiras_{fct}")
        elif (material == "thystame"):
            return self.broadcast(f"{self.team_name}_thystame_{fct}")

    def check_inventory(self):
        for item, required_amount in self.current_inventory.objective_inventory.items():
            total_amount = self.current_inventory.current_inventory.get(item, 0) + self.current_inventory.shared_inventory.get(item, 0)
            if total_amount < required_amount:
                return False
        return True

    def check_item(self, item):
        if item in self.current_inventory.objective_inventory:
            total_amount = self.current_inventory.current_inventory.get(item, 0) + self.current_inventory.shared_inventory.get(item, 0)
            return total_amount >= self.current_inventory.objective_inventory[item]
        else:
            return False

    def pop_item(self, item, from_inventory='objective'):
        if from_inventory == 'current':
            return self.current_inventory.current_inventory.pop(item, None)
        elif from_inventory == 'shared':
            return self.current_inventory.shared_inventory.pop(item, None)
        elif from_inventory == 'objective':
            return self.current_inventory.objective_inventory.pop(item, None)
        else:
            raise ValueError("from_inventory must be either 'current' or 'shared' or 'objective'")

    def get_status(self):
        return self.status

    def nb_player_ready(self):
        return self.player_ready