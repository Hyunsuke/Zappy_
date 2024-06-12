#!/usr/bin/env python3

import socket
import sys
from sys import argv, exit, stdout
from InventoryManager import InventoryManager
from Command import Command
import time


class ZappyClient:
    def __init__(self):
        self.parse_arguments()
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((self.host, self.port))
            self.buffer = ""
            self.level = 1
            self.initial_handshake()
            self.cmd = Command(self.socket)
            self.current_inventory = InventoryManager()
            self.current_inventory.update_inventory(self.cmd.inventory())
            self.main_loop()
        except socket.error as e:
            print(f"Socket error: {e}")
            sys.exit(1)


    def parse_arguments(self):
        for i in argv:
            if (i == "-p"):
                self.port = int(argv[argv.index(i) + 1])
            elif (i == "-n"):
                self.team_name = argv[argv.index(i) + 1]
            elif (i == "-h"):
                self.host = argv[argv.index(i) + 1]

    def initial_handshake(self):
        try:
            welcome_message = self.socket.recv(1024).decode().strip()
            if welcome_message != "WELCOME":
                raise ValueError("Did not receive welcome message")

            self.socket.sendall(f"{self.team_name}\n".encode())
            result = self.socket.recv(1024).decode().strip()
            res = result.split("\n")
            self.client_num  = int(res[0])
            world_dimensions = res[1].split(" ")
            self.width, self.height = int(world_dimensions[0]), int(world_dimensions[1])
            print(f"Connected to server. Client number: {self.client_num}")
            print(f"World dimensions: {self.width}x{self.height}")

        except Exception as e:
            print(f"Handshake error: {e}")
            sys.exit(1)


    # List de ce qu'on doit avoir entre le niveau 2 & 10. L'algo doit prendre ça en compte à partir du lvl2
    finalObjectiveList = [
        ("linemate", 10),
        ("deraumere", 5),
        ("sibur", 20),
        ("mendiane", 7),
        ("phiras", 3),
        ("thystame", 12)
    ]

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
            self.broadcast("[teamname]_linemate")
        elif (material == "deraumere"):
            self.broadcast("[teamname]_deraumere")
        elif (material == "sibur"):
            self.broadcast("[teamname]_sibur")
        elif (material == "mendiane"):
            self.broadcast("[teamname]_mendiane")
        elif (material == "phiras"):
            self.broadcast("[teamname]_phiras")
        elif (material == "thystame"):
            self.broadcast("[teamname]_thystame")

    def main_loop(self):
        try:
            while True:
                self.current_inventory.update_inventory(self.cmd.inventory())
                self.cmd.move_forward()
                if self.current_inventory.current_inventory['food'] < 5:
                    self.eat_nearest_food(True)
        except KeyboardInterrupt:
            print("Terminating AI client.")
        finally:
            self.socket.close()

    def eat_nearest_food(self, needPrint=False):
        response = self.cmd.look()
        if response is None:
            return
        a = 0
        objects = response.split(",")
        for object in objects:
            object = object.split(" ")
            for obj in object:
                if obj.startswith("food"):
                    print("Moving to tile: ", a)
                    self.move_to_tile(a, needPrint)
                    self.cmd.take_object("food")
                    return
            a += 1

    def move_to_tile(self, target_tile, needPrint=False):
        self.cmd.look(needPrint)
        if target_tile == 0:
            return
        a = 0
        b = 0
        tab = []
        for i in range(9): ## max level + 1
            tab.append([])
            b = (i * 2) + 1
            a += b
            b = a - b
            while b < a:
                tab[i].append(b)
                b += 1
        c = 0
        for i in tab:
            tmp = i
            if c != 0:
                self.cmd.move_forward(needPrint)
            if target_tile <= i[-1]:
                break
            c += 1
        c = tmp[-1] -c
        if target_tile < c:
            self.cmd.turn_left(needPrint)
            while c != target_tile:
                self.cmd.move_forward(needPrint)
                c -= 1
        elif target_tile > c:
            self.cmd.turn_right(needPrint)
            while c != target_tile:
                self.cmd.move_forward(needPrint)
                c += 1
        self.cmd.look(needPrint)

if __name__ == "__main__":
    client = ZappyClient()
