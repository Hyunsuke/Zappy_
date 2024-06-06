#!/usr/bin/env python3

import socket
import sys
from sys import argv, exit, stdout
from InventoryManager import InventoryManager
from Command import Command
import time
import os


class ZappyClient:
    def __init__(self):
        self.parse_arguments()
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((self.host, self.port))
            self.buffer = ""
            self.level = 1
            self.initial_handshake()
            self.current_inventory = InventoryManager()
            self.cmd = Command(self.socket, self.current_inventory, self.team_name)
            self.updateInfos()
            self.cmd.sendArrayCmd()
            self.main_loop()
        except socket.error as e:
            print(f"Socket error: {e}")
            os._exit(1)

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


    level_2_objectives = [
        ("linemate", 10),
        ("deraumere", 5),
        ("sibur", 20),
        ("mendiane", 7),
        ("phiras", 3),
        ("thystame", 12)
    ]

    def blockingBuffer(self):
        while self.cmd.getWaitingRoom() > 0:
            continue

    def updateInfos(self):
        self.cmd.inventory()
        self.cmd.look()

    def main_loop(self):
        try:
            while True:
                self.blockingBuffer()
                self.update_inventory()
                # print("Blocking buffered passsed.")
                if self.current_inventory.current_inventory['food'] < 5:
                    self.eat_nearest_ressource("food", False) # Le pb c'est que ça utilse des return d'inventory alors que le code fonctionne plus comme ça
                else:
                    self.look_for_rarest_stone()
                self.cmd.move_forward()
                self.updateInfos()
                self.cmd.sendArrayCmd()

        except KeyboardInterrupt:
            print("Terminating AI client.")
        finally:
            self.socket.close()

    def update_inventory(self, p=False):
        if (self.cmd.isInventoryUpdated == False):
            return
        inventory_string = self.cmd.inventoryString
        if inventory_string is None or inventory_string.startswith("[ food") == False:
            # print("Error: Inventory string is None")
            return
        # Nettoyer et séparer la chaîne de caractères
        inventory_string = inventory_string.strip('[] ')
        items = inventory_string.split(', ')

        # Parcourir les éléments et mettre à jour le dictionnaire
        for item in items:
            # if (item == "ok" or "ko"): # Gestion d'erreur du broadcast
            #     print("Broadcast response: ", item)
            #     return
            key, value = item.split()
            self.current_inventory.current_inventory[key] = int(value)
        if (p == True):
            print("Inventory updated: ", self.current_inventory.current_inventory)

    def eat_nearest_ressource(self, ressource, needPrint=False):
        # print("Eat nearest resource")
        if (self.cmd.isLookUpdated == False):
            return
        # print("We managed to get a look string. Let's eat")
        response = self.cmd.lookString
        if response is None:
            return
        self.cmd.isLookUpdated = False
        a = 0
        objects = response.split(",")
        for object in objects:
            object = object.split(" ")
            for obj in object:
                if obj.startswith(ressource):
                    print("Moving to tile: ", a)
                    self.move_to_tile(a)
                    self.cmd.take_object(ressource)
                    return
            a += 1

    def look_for_rarest_stone(self):
        print("Looking for rarest stone")
        if (self.cmd.isInventoryUpdated == False):
            return
        response = self.cmd.inventoryString
        total_value = 0
        # print(response)
        for key, value in self.current_inventory.objective_inventory.items():
            total_value += value
            # print(key, value)
            if key in response and self.current_inventory.objective_inventory[key] > 0:
                print("Found ", key)
                self.eat_nearest_ressource(key, True)
                self.current_inventory.objective_inventory[key] -= 1
                return
            # if self.current_inventory.current_inventory[key] < value:
            #     self.lookForTile(key)
        if total_value == 0:
            print("All stones have been found")
            os._exit(1)

    def move_to_tile(self, target_tile, needPrint=False):
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

if __name__ == "__main__":
    client = ZappyClient()
