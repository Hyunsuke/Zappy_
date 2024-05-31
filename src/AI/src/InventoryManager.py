#!/usr/bin/env python3

from Command import Command


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

        self.shared_inventory  = {
            'linemate': 0,
            'deraumere': 0,
            'sibur': 0,
            'mendiane': 0,
            'phiras': 0,
            'thystame': 0
        }

        self.objective_inventory = {
            'linemate': 8,
            'deraumere': 8,
            'sibur': 10,
            'mendiane': 5,
            'phiras': 6,
            'thystame': 1
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
            # if (item == "ok" or "ko"): # Gestion d'erreur du broadcast
            #     print("Broadcast response: ", item)
            #     return
            key, value = item.split()
            self.current_inventory[key] = int(value)
        if (p == True):
            print("Inventory updated: ", self.current_inventory)

    def __str__(self):
        return str(self.current_inventory)
