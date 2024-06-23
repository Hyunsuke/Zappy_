#!/usr/bin/env python3

from sys import stdout
import sys
import re
import socket
from InventoryManager import InventoryManager
import threading
import os
from utils import *

class Command:
    def __init__(self, socket, current_inventory, team_name):
        self.status = -1
        self.reset = False
        self.player_ready = 0
        self.inventory_valid = False
        self.joined = False
        self.joiner = 0
        self.player_food_ready = 0
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

    def sendArrayCmd(self):
        while len(self.commandList) != 0:
            try:
                if (self.commandWaitingRoom < 9):
                    if (len(self.commandList) != 0):
                        self.socket.sendall(f"{self.commandList[0]}\n".encode())
                        self.commandList.pop(0)
                        self.commandWaitingRoom += 1
            except socket.error as e:
                print(f"Error sending command '{self.commandList[0]}': {e}")
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
        elif data.startswith("eject"):
            print("Le recv reçu est un eject")
            print(self.data_received)
            return
        else:
            print("We received " + data)
            if not self.responseList:
                return
            self.adjustData()
            if len(self.responseList) > 0:
                if self.responseList[0] != "Incantation":
                    self.commandWaitingRoom -= 1
                self.responseList.pop(0)

    def reception_loop(self):
        while True:
            try:
                data_array = self.getResponseArray()
                for element in data_array:
                    self.processResponseArray(element)

            except socket.error as e:
                print(f"Erreur lors de la réception des données : {e}")
                os._exit(84)

    def adjustData(self):
        if not self.responseList:
            return
        if self.responseList[0].startswith("Take"):
            self.adjustTake()
        elif self.responseList[0].startswith("Set"):
            self.adjustSet()
        elif self.responseList[0].startswith("Incantation"):
            self.adjustIncantation()
        elif self.responseList[0].startswith("Eject"):
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
        elif self.responseList[0].startswith("Look"):
            self.lookString = self.data_received
            self.isLookUpdated = True
        elif self.responseList[0].startswith("Inventory"):
            self.inventoryString = self.data_received
            self.isInventoryUpdated = True

    def positionChanged(self):
        return self.positionHasBeenChanged

    def adjustForward(self):
        if self.leaderIsChosen == -1:
            return
        if self.positionHasBeenChanged == True:
            return
        if self.status == 0:
            return
        if self.status == 1 or self.status == 3 or self.status == 5 or self.status == 7:
            self.positionHasBeenChanged = True
        else:
            self.forwardIndex += 1
            if self.forwardIndex == 2:
                self.positionHasBeenChanged = True
                self.forwardIndex = 0

    def broadcastMaterial(self, material, fct):
        if (material == "linemate"):
            self.broadcast(f"{self.team_name}_linemate_{fct}")
        elif (material == "deraumere"):
            self.broadcast(f"{self.team_name}_deraumere_{fct}")
        elif (material == "sibur"):
            self.broadcast(f"{self.team_name}_sibur_{fct}")
        elif (material == "mendiane"):
            self.broadcast(f"{self.team_name}_mendiane_{fct}")
        elif (material == "phiras"):
            self.broadcast(f"{self.team_name}_phiras_{fct}")
        elif (material == "thystame"):
            self.broadcast(f"{self.team_name}_thystame_{fct}")

    def adjustBroadcast(self):
        broadcastMessage = skip_to_first_comma(self.data_received)
        num = recuperer_chiffre(self.data_received)
        team_name, object, fct = getBroadcastMessage(broadcastMessage)
        if team_name == None or object == None or fct == None:
            return
        if team_name == self.team_name:
            print("Name : " + team_name + " object : " + object + " fct : " + fct + " num : " + str(num))
            if fct == "Take":
                if object in self.current_inventory.shared_inventory:
                    self.current_inventory.shared_inventory[object] += 1
                    self.validateInventory(object)
            elif fct == "OK":
                if object in self.current_inventory.shared_inventory:
                    print("Il faut pop l'objet du objective inventory")
                    self.validateInventory(object, True)
            elif fct == "END":
                if self.leaderIsChosen == 1:
                    return
                self.leaderIsChosen = 0
                if self.joined == False:
                    self.broadcast(f"{self.team_name}_ready_joiner")
                    self.joined = True
                self.status = 11
                print("Je vais rejoindre l'émetteur du message")
            elif fct == "ready" and object == "ready" and self.leaderIsChosen == 1:
                self.player_ready += 1
                if self.player_ready >= 5:
                    print("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||")
                return
            elif fct == "ready" and object == "food" and self.leaderIsChosen == 1:
                self.player_food_ready += 1
                if self.player_food_ready == 5:
                    print("player_food_ready")
            elif fct == "come":
                if self.joined == False:
                    self.broadcast(f"{self.team_name}_ready_joiner")
                    self.joined = True
                if self.positionHasBeenChanged == True:
                    if self.shallMove == False:
                        self.status = num
                        self.shallMove = True
            elif fct == "gather":
                if self.joined == False:
                    self.broadcast(f"{self.team_name}_ready_joiner")
                    self.joined = True
                self.status = 10
            elif fct == "joiner" and self.leaderIsChosen == 1:
                print("J4AI UN POTE")
                self.joiner += 1
            elif fct == "os":
                os._exit(1)
            elif fct == "reset":
                self.reset_command()

    def elevate(self):
        return self.hasElevated

    def shouldMove(self):
        return self.shallMove

    def adjustEject(self):
        return

    def adjustIncantation(self):
        # Le booléen de l'incantation doit être mis sur false
        if self.data_received == "ko":
            if (self.leaderIsChosen == 1):
                self.broadcast(f"{self.team_name}_reset_reset")
                self.reset_command()
                return
            self.responseList.pop(1)
            self.commandWaitingRoom -= 1 # C'est parce que Incantation est la seule commande à envoyer 2 recv
            return

    def adjustSet(self):
        response = self.responseList[0].split(' ')
        objectTaken = response[1]
        if self.data_received == "ko":
            return
        if self.level == 1:
            return

    def validateInventory(self, objectTaken, broadcast=False):
        if check_inventory(self.current_inventory) == True:
            print("Tous les items ont été trouvés. Go faire le passage lvl8")
            self.broadcastMaterial(objectTaken, "END")
            return True
        if check_item(objectTaken, self.current_inventory) == True:
            if broadcast == False and objectTaken != "food":
                self.broadcastMaterial(objectTaken, "OK")
            return True
        return False

    def adjustTake(self):
        # Augmenter le shared inventory de 1
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


    def pop_item(self, item, from_inventory='objective'):
        if from_inventory == 'current':
            return self.current_inventory.current_inventory.pop(item, None)
        elif from_inventory == 'shared':
            return self.current_inventory.shared_inventory.pop(item, None)
        elif from_inventory == 'objective':
            return self.current_inventory.objective_inventory.pop(item, None)
        else:
            raise ValueError("from_inventory must be either 'current' or 'shared' or 'objective'")

    def reset_command(self):
        self.status = -1
        self.reset = False
        self.player_ready = 0
        self.inventory_valid = False
        self.joined = False
        self.joiner = 0
        self.player_food_ready = 0
        self.elevation = False
        self.data_received = ""
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

        self.reset = True

    def get_status(self):
        return self.status

    def nb_player_ready(self):
        return self.player_ready

    def nb_player_food_ready(self):
        return self.player_food_ready

    def nb_joiner_ready(self):
        return self.joiner

    def get_reset(self):
        return self.reset
