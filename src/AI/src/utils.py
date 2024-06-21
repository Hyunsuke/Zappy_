# This file contains some useful functions for the AI

import random

def get_cood(num):
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


def get_coordinates(target_tile):
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
        while c != target_tile:
            x -= 1
            c -= 1
    elif target_tile > c:
        while c != target_tile:
            x += 1
            c += 1
    return x, y  # If tile not found (which shouldn't happen in this context)

def random_nb(self):
    return random.choice([0, 1, 2])
