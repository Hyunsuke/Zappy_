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
        self.commandList = []
        thread_reception = threading.Thread(target=self.reception_loop)
        thread_reception.start()
        thread_send = threading.Thread(target=self.sendArrayCmd)
        thread_send.start()


    def sendArrayCmd(self):
        while True:
            try:
                if (self.commandWaitingRoom < 0):
                    print("Debuggingggggggggggggggggggggggg")
                if (self.commandWaitingRoom < 10):
                    if (len(self.commandList) != 0):
                        self.socket.sendall(f"{self.commandList[0]}\n".encode())
                        self.commandWaitingRoom += 1
                        self.commandList.pop(0)
            except socket.error as e:
                print(f"Error sending command '{self.commandList[0]}': {e}")
                # return None
                sys.exit(84)


    def send_command(self, command):
        self.commandList.append(command)

    def reception_loop(self):
        while True:
            try:
                # Recevoir des données depuis le socket
                data = self.socket.recv(1024).decode().strip()
                if not data:
                    # Gérer la déconnexion ou la fin de la communication
                    print("Déconnexion du serveur")
                    break
                if data == "dead":
                    print("Dead then exit")
                    os._exit(0)
                self.data_received = data
                if (data != "ko"): # Et aussi différent d'un broadcast, faut voir.
                    self.commandWaitingRoom -= 1
                # Imprimer les données reçues
                print("Données reçues :", data)
            except socket.error as e:
                print(f"Erreur lors de la réception des données : {e}")
                break

    def move_forward(self, needPrint=False):
        response = self.send_command("Forward")
        if needPrint:
            print("Move forward : " + response)
        return response

    def turn_right(self, needPrint=False):
        response = self.send_command("Right")
        if needPrint:
            print("Turn right : " + response)
        return response

    def turn_left(self, needPrint=False):
        response = self.send_command("Left")
        if needPrint:
            print("Turn left : " + response)
        return response

    def look(self, needPrint=False):
        response = self.send_command("Look")
        if needPrint:
            print("Look : " + response)
        return response

    def inventory(self, needPrint=False):
        response = self.send_command("Inventory")
        if needPrint:
            print("Inventory : " + response)
        return response

    def broadcast(self, message):
        return self.send_command(f"Broadcast {message}")

    def connect_nbr(self, needPrint=False):
        response = self.send_command("Connect_nbr")
        if needPrint:
            print("Connect_nbr : " + response)
        return response

    def fork(self, needPrint=False):
        response = self.send_command("Fork")
        if needPrint:
            print("Fork : " + response)
        return response

    def eject(self, needPrint=False):
        response = self.send_command("Eject")
        if needPrint:
            print("Eject : " + response)
        return response

    def take_object(self, object):
        print("Take object : " + self.send_command("Take " + object))
        if object in self.current_inventory.current_inventory:
            self.current_inventory.current_inventory[object] += 1
            if object != "food":
                # self.broadcastMaterial(object)
                self.current_inventory.shared_inventory[object] += 1

    def set_object_down(self, object):
        print("Set object : " + self.send_command("Set " + object))
        if object in self.current_inventory.current_inventory:
            if self.current_inventory.current_inventory[object] > 0:
                self.current_inventory.current_inventory[object] -= 1
                if object != "food":
                    # self.broadcastMaterial(object)
                    self.current_inventory.shared_inventory[object] -= 1


    def incantation(self, needPrint=False):
        response = self.send_command("Incantation")
        if needPrint:
            print("Incantation : " + response)
        return response

    def getBroadcastMessage(self, response):
        if (response == "ok" or response == "ko"):
            return response
        parts = response('_')
        if len(parts) != 2:
            raise ValueError("La chaîne d'entrée n'est pas au format 'teamname_object'")
        # On récupère le nom de l'équipe et l'objet
        team_name = parts[0]
        object_name = parts[1]
        return team_name, object_name

    def broadcastMaterial(self, material):
        if (material == "linemate"):
            return self.broadcast(f"[{self.team_name}]_linemate")
        elif (material == "deraumere"):
            return self.broadcast(f"[{self.team_name}]_deraumere")
        elif (material == "sibur"):
            return self.broadcast(f"[{self.team_name}]_sibur")
        elif (material == "mendiane"):
            return self.broadcast(f"[{self.team_name}]_mendiane")
        elif (material == "phiras"):
            return self.broadcast(f"[{self.team_name}]_phiras")
        elif (material == "thystame"):
            return self.broadcast(f"[{self.team_name}]_thystame")
