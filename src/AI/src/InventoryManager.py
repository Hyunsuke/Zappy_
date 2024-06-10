#!/usr/bin/env python3

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

    def __str__(self):
        return str(self.current_inventory)
