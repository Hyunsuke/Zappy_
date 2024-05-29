#!/usr/bin/env python3

import socket
import sys
from sys import argv, exit, stdout
import time


class InventoryManager:
    def __init__(self):
        self.current_inventory = {
            'food': 0,
            'linemate': 0,
            'deraumere': 0,
            'sibur': 0,
            'mendiane': 0,
            'phiras': 0,
            'thystame': 0
        }

    def update_inventory(self, inventory_string, p=False):
        if inventory_string is None:
            print("Error: Inventory string is None")
            return
        # Nettoyer et séparer la chaîne de caractères
        inventory_string = inventory_string.strip('[] ')
        items = inventory_string.split(', ')

        # Parcourir les éléments et mettre à jour le dictionnaire
        for item in items:
            key, value = item.split()
            self.current_inventory[key] = int(value)
        if p == True:
            print("Inventory updated: ", self.current_inventory)

    def __str__(self):
        return str(self.current_inventory)



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
            self.current_inventory.update_inventory(self.inventory())
            self.main_loop()
        except socket.error as e:
            print(f"Socket error: {e}")
            sys.exit(1)


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

    def move_forward(self):
        response = self.send_command("Forward")
        if print == True:
            print("Move forward : " + response)

    def turn_right(self):
        response = self.send_command("Right")
        if print == True:
            print("Turn right : " + response)

    def turn_left(self):
        response = self.send_command("Left")
        if print == True:
            print("Turn left : " + response)

    def look(self):
        return self.send_command("Look")

    def inventory(self):
        return self.send_command("Inventory")

    def broadcast(self, message):
        print("Broadcast : " + self.send_command(f"Broadcast {message}"))

    def take_object(self, object):
        print("Take object : " + self.send_command("Take " + object))

    def main_loop(self):
        try:
            while True:
                self.current_inventory.update_inventory(self.inventory())
                self.move_forward()
                # self.move_forward()
                # self.look()
                # self.take_object("food")
                # self.current_inventory.update_inventory(self.inventory())
                if self.current_inventory.current_inventory['food'] < 5:
                    self.eat_nearest_food()
                    # sys.exit(1)
        except KeyboardInterrupt:
            print("Terminating AI client.")
        finally:
            self.socket.close()

    def eat_nearest_food(self):
        response = self.look()
        if response is None:
            return
        a = 0
        objects = response.split(",")
        for object in objects:
            object = object.split(" ")
            for obj in object:
                if obj.startswith("food"):
                    # print("Found food!")
                    # print(f"Response: {response}")
                    print("Moving to tile: ", a)
                    print("Food " + str(self.current_inventory.current_inventory['food']))
                    self.move_to_tile(a)
                    self.take_object("food")
                    print("Food " + str(self.current_inventory.current_inventory['food']))
                    return
            a += 1

    def move_to_tile(self, target_tile):
        vision = self.look()

        if target_tile == 0:
            return  # Already at the target tile

        # Determine the direction and distance to the target tile
        current_level = int((len(vision) ** 0.5 - 1) / 2)
        distance = 1
        while distance * distance <= target_tile:
            distance += 1
        distance -= 1

        if self.level > 1:
            while target_tile >= distance:
                target_tile -= distance
                self.move_forward()

        # Adjust direction
        if target_tile == 1:
            self.turn_left()
            self.move_forward()
            self.turn_right()
        elif target_tile == 2:
            self.move_forward()
        elif target_tile == 3:
            self.turn_right()
            self.move_forward()
            self.turn_left()

        self.look()  # Refresh vision to confirm

if __name__ == "__main__":
    client = ZappyClient()
