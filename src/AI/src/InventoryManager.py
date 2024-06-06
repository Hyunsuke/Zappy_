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

        # List de ce qu'on doit avoir entre le niveau 2 & 8. L'algo doit prendre ça en compte à partir du lvl 2
        self.objective_inventory = {
            'thystame': 1,
            'phiras': 6,
            'mendiane': 5,
            'sibur': 10,
            'deraumere': 8,
            'linemate': 8
        }

    def __str__(self):
        return str(self.current_inventory)
