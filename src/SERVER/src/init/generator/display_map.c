/*
** EPITECH PROJECT, 2024
** generator_map.c
** File description:
** Function generator_map
*/

#include "server.h"

static void print_map_element(map_element_t *element, int client_nb)
{
    printf("food: %s\n", element->food ? "true" : "false");
    printf("linemate: %s\n", element->linemate ? "true" : "false");
    printf("deraumere: %s\n", element->deraumere ? "true" : "false");
    printf("sibur: %s\n", element->sibur ? "true" : "false");
    printf("mendiane: %s\n", element->mendiane ? "true" : "false");
    printf("phiras: %s\n", element->phiras ? "true" : "false");
    printf("thystame: %s\n", element->thystame ? "true" : "false");
    printf("id_mob: ");
    for (int i = 0; i < client_nb; i++)
        printf("%d ", element->id_mob[i]);
    printf("\n");
}

void print_map(struct_t *s)
{
    for (int y = 0; y < s->map_height; y++) {
        for (int x = 0; x < s->map_width; x++) {
            printf("Cell (%d, %d):\n", y, x);
            print_map_element(&(s->map[y][x]), s->client_nb);
            printf("\n");
        }
    }
}
