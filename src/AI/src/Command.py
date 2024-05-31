#!/usr/bin/env python3

from sys import stdout
import sys
import socket

class Command:
    def __init__(self, socket):
        self.socket = socket

    def send_command(self, command):
        try:
            self.socket.sendall(f"{command}\n".encode())
            response = self.socket.recv(1024).decode().strip()
            if response == "dead":
                print("Dead")
                sys.exit(1)
            return response
        except socket.error as e:
            print(f"Error sending command '{command}': {e}")
            return None

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

    def set_object_down(self, object):
        print("Set object : " + self.send_command("Set " + object))

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
            return self.broadcast("[teamname]_linemate")
        elif (material == "deraumere"):
            return self.broadcast("[teamname]_deraumere")
        elif (material == "sibur"):
            return self.broadcast("[teamname]_sibur")
        elif (material == "mendiane"):
            return self.broadcast("[teamname]_mendiane")
        elif (material == "phiras"):
            return self.broadcast("[teamname]_phiras")
        elif (material == "thystame"):
            return self.broadcast("[teamname]_thystame")
