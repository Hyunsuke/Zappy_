#!/usr/bin/env python3

import socket
import sys
from sys import argv, exit, stdout
from InventoryManager import InventoryManager
from Command import Command
import time
import os
import random


class ZappyClient:
    def __init__(self):
        self.parse_arguments()
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((self.host, self.port))
            self.buffer = ""
            self.priorityList = ["food", "thystame", "linemate"]
            self.initial_handshake()
            self.current_inventory = InventoryManager()
            self.cmd = Command(self.socket, self.current_inventory, self.team_name)
            self.ready = False
            self.food_ready = False
            self.updateInfos()
            self.cmd.fork()
            self.cmd.sendArrayCmd()
            self.dropped = False
            self.printReady = True
            self.fastLvl2()
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
        if self.ready == False:
            self.cmd.inventory()
            self.cmd.look()

    def random_nb(self):
        return random.choice([0, 1, 2])

    def rotatePlayer(self):
        nb = self.random_nb()
        if nb == 0:
            return
        elif nb == 1:
            self.cmd.turn_left()
        elif nb == 2:
            self.cmd.turn_right()

    def fastLvl2(self):
        i = 0
        try:
            while True:
                self.blockingBuffer()
                self.update_inventory()
                if self.current_inventory.current_inventory['food'] >= 10 and self.current_inventory.current_inventory['linemate'] >= 1:
                    self.cmd.set_object_down("linemate")
                    self.cmd.incantation()
                    self.cmd.responseList.append("Current level")
                    self.cmd.fork()
                    self.updateInfos()
                    self.cmd.sendArrayCmd()
                    self.blockingBuffer()
                    if self.cmd.elevate() == True:
                        self.cmd.hasElevated = False
                        break
                    else:
                        continue
                self.eat_nearest_ressource("linemate", False) # Le pb c'est que ça utilse des return d'inventory alors que le code fonctionne plus comme ça
                self.rotatePlayer()
                self.cmd.move_forward()
                self.updateInfos()
                self.cmd.sendArrayCmd()
        except KeyboardInterrupt:
            print("Terminating AI client.")
            self.socket.close()
            os._exit(0)

    def main_loop(self):
        try:
            while True:
                self.blockingBuffer()
                self.update_inventory()
                # print(self.cmd.get_status())
                if self.cmd.get_status() == -2:
                    if self.ready == True:
                        self.cmd.incantation()
                        self.cmd.responseList.append("Current level")
                    elif self.cmd.nb_player_ready() >= 5 and self.ready == False:
                        print("EVERYONE'S READY TO PLAY")
                        self.cmd.look()
                        self.ready = True
                        self.drop_all(True)
                    elif self.cmd.nb_player_food_ready() >= 5 and self.ready == False and self.current_inventory.current_inventory["food"] > 30:
                        self.cmd.broadcast(f"{self.team_name}_ready_come")
                    else:
                        print("waiting for friends")
                        self.cmd.broadcast(f"{self.team_name}_ready_gather")
                        self.eat_nearest_ressource("food")
                elif self.cmd.get_status() >= 0 and self.cmd.get_status() < 10 and self.ready == False:
                    if self.cmd.shouldMove() == True and self.cmd.positionChanged() == True:
                        self.join_leader()
                    # break
                elif self.ready == True:
                    if self.printReady == True:
                        print("I'm ready")
                        self.printReady = False
                    if self.dropped == False:
                        self.drop_all()
                    # self.cmd.look()
                    # break
                elif self.cmd.get_status() == 10:
                    print("(((((((((((((((((((((((((((())))))))))))))))))))))))))))")
                    print(self.current_inventory.current_inventory["food"])
                    if self.current_inventory.current_inventory["food"] > 30 and self.food_ready == False:
                        self.cmd.broadcast(f"{self.team_name}_food_ready")
                        self.food_ready = True
                    self.eat_nearest_ressource("food")
                else:
                    print("---------------------------")
                    if self.current_inventory.current_inventory['food'] < 15:
                        self.eat_nearest_ressource("food", False)
                    else:
                        self.look_for_rarest_stone()
                    self.rotatePlayer()
                    self.cmd.move_forward()
                    self.cmd.move_forward()
                self.updateInfos()
                self.cmd.sendArrayCmd()

        except KeyboardInterrupt:
            print("Terminating AI client.")
        finally:
            self.socket.close()
            os._exit(0)

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
            self.cmd.current_inventory.current_inventory[key] = int(value)
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
        # tiles_with_resource = []
        destinationTile = 0
        currentTile = 0
        objects = response.split(",")
        for object in objects:
            object = object.split(" ")
            for obj in object:
                if obj.startswith(ressource) or obj.startswith("food"):
                    # tiles_with_resource.append(destinationTile)
                    print("Moving to tile: ", destinationTile)
                    x, y = self.get_coordinates(destinationTile)
                    current_x, current_y = self.get_coordinates(currentTile)
                    print("x: ", x, "y: ", y)
                    self.move_to_tile(x, y, current_x, current_y)
                    currentTile = destinationTile
                    if obj.startswith("food"):
                        self.cmd.take_object("food")
                    else :
                        self.cmd.take_object(ressource)
                    # return
            destinationTile += 1

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
                # print("Found ", key)
                total_amount = self.cmd.current_inventory.current_inventory.get(key, 0) + self.cmd.current_inventory.shared_inventory.get(key, 0)
                print(key, ": ", total_amount)
                if total_amount < self.cmd.current_inventory.objective_inventory[key]:
                    self.eat_nearest_ressource(key, True)
                # self.current_inventory.objective_inventory[key] -= 1
                    return
            # if self.current_inventory.current_inventory[key] < value:
            #     self.lookForTile(key)
        # if total_value == 0:
        #     print("All stones have been found")
        #     os._exit(1)

    def move_to_tile(self, target_x, target_y, current_x, current_y, needPrint=False):
        # Move in the X direction
        while current_x != target_x:
            if current_x < target_x:
                self.cmd.turn_right(needPrint)
                while current_x < target_x:
                    self.cmd.move_forward(needPrint)
                    current_x += 1
                self.cmd.turn_left(needPrint)
            elif current_x > target_x:
                self.cmd.turn_left(needPrint)
                while current_x > target_x:
                    self.cmd.move_forward(needPrint)
                    current_x -= 1
                self.cmd.turn_right(needPrint)

        # Move in the Y direction
        while current_y != target_y:
            if current_y < target_y:
                while current_y < target_y:
                    self.cmd.move_forward(needPrint)
                    current_y += 1
            elif current_y > target_y:
                self.cmd.turn_left(needPrint)
                self.cmd.turn_left(needPrint)
                while current_y > target_y:
                    self.cmd.move_forward(needPrint)
                    current_y -= 1
                self.cmd.turn_left(needPrint)
                self.cmd.turn_left(needPrint)

    def get_coordinates(self, target_tile):
        if target_tile == 0:
            return (0, 0)

        a = 0
        b = 0
        tab = []
        for i in range(9):  # max level + 1
            tab.append([])
            b = (i * 2) + 1
            a += b
            b = a - b
            while b < a:
                tab[i].append(b)
                b += 1

        c = 0
        x = 0
        y = 0
        for i in tab:
            tmp = i
            if c != 0:
                y += 1
            if target_tile <= i[-1]:
                break
            c += 1
        c = tmp[-1] -c
        if target_tile < c:
            # self.cmd.turn_left(needPrint)
            while c != target_tile:
                x -= 1
                c -= 1
        elif target_tile > c:
            # self.cmd.turn_right(needPrint)
            while c != target_tile:
                x += 1
                c += 1
        return x, y  # If tile not found (which shouldn't happen in this context)

    def get_cood(self, num):
        if num == 0:
            return
        mov = {
            1: (0, 1),
            2: (-1, 1),
            3: (-1, 0),
            4: (-1, -1),
            5: (0, -1),
            6: (1, -1),
            7: (1, 0),
            8: (1, 1)
        }

        if num not in mov:
            raise ValueError("Le numéro doit être entre 1 et 8")

        dx, dy = mov[num]
        return dx, dy


    def join_leader(self):
        print("IM JOINING THE LEADER")
        status = self.cmd.get_status()
        if status == 0 and self.ready == False:
            print("-----------------------------------------------------------------------------------------------")
            print("Je suis prêt")
            self.ready = True
            print("-----------------------------------------------------------------------------------------------")
            # os._exit(1)
            return
        x, y = self.get_cood(status)
        self.move_to_tile(x, y, 0, 0)
        self.cmd.shallMove = False
        self.cmd.positionHasBeenChanged = False

    def drop_all(self, leads=False):
        for key, value in self.current_inventory.current_inventory.items():
            # print("Dropping all  {}".format(key))
            if key == "food":
                continue
            for i in range(value):
                print(key)
                self.cmd.set_object_down(key)
        if leads == False:
            self.cmd.broadcast(f"{self.team_name}_ready_ready")
        self.dropped = True



if __name__ == "__main__":
    client = ZappyClient()
