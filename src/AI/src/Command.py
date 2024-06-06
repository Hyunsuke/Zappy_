#!/usr/bin/env python3

from sys import stdout
import sys
import socket
from InventoryManager import InventoryManager
import threading
import os


class Command:
    def __init__(self, socket, current_inventory, team_name):
        self.team_name = team_name
        self.socket = socket
        self.current_inventory = current_inventory
        self.data_received = ""
        self.commandWaitingRoom = 0
        self.dataIndex = 0
        self.debug = 0
        self.lookString = ""
        self.isLookUpdated = False
        self.inventoryString = ""
        self.isInventoryUpdated = False
        self.commandList = []
        self.responseList = []
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
                else:
                    break
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
            print("We received " + data + " for command " + self.responseList[0])
            self.adjustData()
            self.responseList.pop(0)
            self.commandWaitingRoom -= 1

    def reception_loop(self):
        while True:
            try:
                data_array = self.getResponseArray()
                for element in data_array:
                    self.processResponseArray(element)

            except socket.error as e:
                print(f"Erreur lors de la réception des données : {e}")
                break

    def adjustData(self):
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
        if self.responseList[0].startswith("Look"):
            self.lookString = self.data_received
            self.isLookUpdated = True
        if self.responseList[0].startswith("Inventory"):
            self.inventoryString = self.data_received
            self.isInventoryUpdated = True

    def adjustBroadcast(self):
        # print("Données reçu : " + self.data_received)
        broadcastMessage = self.skip_to_first_comma(self.data_received)
        print(broadcastMessage)
        team_name, object, fct = self.getBroadcastMessage(broadcastMessage)
        print("Name : " + team_name + " object : " + object + " fct : " + fct)
        if team_name == self.team_name:
            if fct == "Take":
                if object in self.current_inventory.shared_inventory:
                    self.current_inventory.shared_inventory[object] += 1
                    # Check si current inventory + shared inventory >= objective inventory
            if fct == "OK":
                if object in self.current_inventory.shared_inventory:
                    print("Il faut pop l'objet du shared inventory")
                # Check si on a atteint l'objectif
        # if (self.data_received)

    def skip_to_first_comma(self, string):
        pos = string.find(',')
        if pos != -1:
            return string[pos + 2:]  # Récupère la sous-chaîne après la première virgule et l'espace
        else:
            # Si aucune virgule n'est trouvée, retourne la chaîne originale
            return string

    def adjustEject(self):
        return

    def adjustIncantation(self):
        # Le booléen de l'incantation doit être mis sur false
        return

    def adjustSet(self):
        # Baisser le shared inventory de 1
        cmd, object = self.responseList[0]
        if self.data_received == "ko":
            return
        if object in self.current_inventory.shared_inventory:
            if self.current_inventory.shared_inventory[object] > 0:
                self.current_inventory.shared_inventory[object] -= 1

    def adjustTake(self):
        # Augmenter le shared inventory de 1
        # cmd, object = self.responseList[0]
        response = self.responseList[0].split(' ')
        objectTaken = response[1]
        # Check si c'est ok
        if self.data_received == "ko":
            return
        if objectTaken in self.current_inventory.shared_inventory:
            self.broadcastMaterial(objectTaken, "Take")
            if self.current_inventory.shared_inventory[objectTaken] > 0:
                self.current_inventory.shared_inventory[objectTaken] += 1

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
        # print("Take object : " + object)
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
