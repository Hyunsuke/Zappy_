#!/usr/bin/env python3

import socket
import sys
import argparse
from sys import argv, exit, stdout
from InventoryManager import InventoryManager
from Command import Command
import os
from utils import *


class ZappyClient:
    def __init__(self, host, port, team_name):
        self.host = host
        self.port = port
        self.team_name = team_name

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
        except KeyboardInterrupt:
            print("Terminating AI client.")
            self.socket.close()
            os._exit(0)

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

    def blockingBuffer(self):
        while self.cmd.getWaitingRoom() > 0:
            continue

    def updateInfos(self):
        if self.ready == False:
            self.cmd.inventory()
            self.cmd.look()

    def rotatePlayer(self):
        nb = random_nb()
        if nb == 0:
            return
        elif nb == 1:
            self.cmd.turn_left()
        elif nb == 2:
            self.cmd.turn_right()

    def fastLvl2(self):
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
                self.eat_nearest_ressource("linemate", False)
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
                if self.cmd.get_reset == True:
                    self.reset_main()
                    continue
                if self.cmd.get_status() == -2:
                    if self.ready == True:
                        print(self.cmd.nb_joiner_ready())
                        print(self.cmd.nb_player_ready())
                        self.cmd.incantation()
                        self.cmd.responseList.append("Current level")
                    elif self.cmd.nb_player_ready() == self.cmd.nb_player_food_ready() and self.cmd.nb_player_food_ready() >= 5 and self.ready == False:
                        print("EVERYONE'S READY TO PLAY")
                        self.cmd.look()
                        self.ready = True
                        self.drop_all(True)
                    elif self.cmd.nb_player_food_ready() == self.cmd.nb_joiner_ready() and self.cmd.nb_joiner_ready() >= 5 and self.ready == False:
                        self.cmd.broadcast(f"{self.team_name}_ready_come")
                    elif self.cmd.nb_joiner_ready() >= 5 and self.ready == False:
                        self.cmd.broadcast(f"{self.team_name}_ready_gather")
                        self.eat_nearest_ressource("food")
                        print("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$")
                        print(self.current_inventory.current_inventory["food"])
                        print(self.cmd.nb_joiner_ready())
                        print(self.cmd.nb_player_food_ready())
                    else:
                        print("waiting for friends")
                        self.eat_nearest_ressource("food")
                        print("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$")
                        print(self.current_inventory.current_inventory["food"])
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
                elif self.cmd.get_status() >= 10:
                    print("(((((((((((((((((((((((((((())))))))))))))))))))))))))))")
                    print(self.current_inventory.current_inventory["food"])
                    if self.current_inventory.current_inventory["food"] > 30 and self.food_ready == False and self.cmd.get_status() == 10:
                        self.cmd.broadcast(f"{self.team_name}_food_ready")
                        self.food_ready = True
                        # os._exit(0)
                    self.eat_nearest_ressource("food")
                else:
                    print("-------------------------------------------------------------------------------------------")
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
            return
        # Nettoyer et séparer la chaîne de caractères
        inventory_string = inventory_string.strip('[] ')
        items = inventory_string.split(', ')

        # Parcourir les éléments et mettre à jour le dictionnaire
        for item in items:
            key, value = item.split()
            self.current_inventory.current_inventory[key] = int(value)
            self.cmd.current_inventory.current_inventory[key] = int(value)
        if (p == True):
            print("Inventory updated: ", self.current_inventory.current_inventory)

    def eat_nearest_ressource(self, ressource, needPrint=False):
        if (self.cmd.isLookUpdated == False):
            return
        response = self.cmd.lookString
        if response is None:
            return
        self.cmd.isLookUpdated = False
        destinationTile = 0
        currentTile = 0
        objects = response.split(",")
        for object in objects:
            object = object.split(" ")
            for obj in object:
                if obj.startswith(ressource) or obj.startswith("food"):
                    print("Moving to tile: ", destinationTile)
                    x, y = get_coordinates(destinationTile)
                    current_x, current_y = get_coordinates(currentTile)
                    print("x: ", x, "y: ", y)
                    self.move_to_tile(x, y, current_x, current_y)
                    currentTile = destinationTile
                    if obj.startswith("food"):
                        self.cmd.take_object("food")
                    else :
                        self.cmd.take_object(ressource)
            destinationTile += 1

    def look_for_rarest_stone(self):
        print("Looking for rarest stone")
        if (self.cmd.isInventoryUpdated == False):
            return
        response = self.cmd.inventoryString
        total_value = 0
        for key, value in self.current_inventory.objective_inventory.items():
            total_value += value
            if key in response and self.current_inventory.objective_inventory[key] > 0:
                total_amount = self.cmd.current_inventory.current_inventory.get(key, 0) + self.cmd.current_inventory.shared_inventory.get(key, 0)
                print(key, ": ", total_amount)
                if total_amount < self.cmd.current_inventory.objective_inventory[key]:
                    self.eat_nearest_ressource(key, True)
                    return

    def move_to_tile(self, target_x, target_y, current_x, current_y, needPrint=False):
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


    def join_leader(self):
        print("IM JOINING THE LEADER")
        status = self.cmd.get_status()
        if status == 0 and self.ready == False:
            print("-----------------------------------------------------------------------------------------------")
            print("Je suis prêt")
            self.ready = True
            print("-----------------------------------------------------------------------------------------------")
            return
        x, y = get_cood(status)
        self.move_to_tile(x, y, 0, 0)
        self.cmd.shallMove = False
        self.cmd.positionHasBeenChanged = False

    def drop_all(self, leads=False):
        for key, value in self.current_inventory.current_inventory.items():
            if key == "food":
                continue
            for i in range(value):
                print(key)
                self.cmd.set_object_down(key)
        if leads == False:
            self.cmd.broadcast(f"{self.team_name}_ready_ready")
        self.dropped = True


    def reset_main(self):
        self.drop_all(True)
        self.buffer = ""
        self.priorityList = ["food", "thystame", "linemate"]
        self.current_inventory = InventoryManager()
        self.cmd = Command(self.socket, self.current_inventory, self.team_name)
        self.ready = False
        self.food_ready = False
        self.updateInfos()
        self.cmd.fork()
        self.cmd.sendArrayCmd()
        self.dropped = False
        self.printReady = True

        self.cmd.reset = False

def parse_arguments():
    parser = argparse.ArgumentParser(description='Zappy AI Client', add_help=False)
    parser.add_argument('-p', '--port', type=int, required=True, help='Port number of the server')
    parser.add_argument('-n', '--team_name', type=str, required=True, help='Name of the team')
    parser.add_argument('-h', '--host', type=str, default='localhost', help='Host address of the server')
    parser.add_argument('--help', action='help', help='Show this help message and exit')

    # Parse the arguments and handle errors
    try:
        args = parser.parse_args()
        if args.port < 0 or args.port > 65535:
            parser.print_help()
            sys.exit(84)
    except argparse.ArgumentError as e:
        print(f"Error: {e}")
        parser.print_help()
        sys.exit(2)
    except SystemExit as e:
        # This will catch argparse's SystemExit exception
        parser.print_help()
        sys.exit(e.code)

    return args.host, args.port, args.team_name

if __name__ == "__main__":
    host, port, team_name = parse_arguments()
    client = ZappyClient(host, port, team_name)
