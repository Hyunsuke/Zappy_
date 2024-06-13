/*
** EPITECH PROJECT, 2024
** init_elevation.c
** File description:
** init_elevation
*/

#include "all.h"

elevation_t *init_elevation(void)
{
    elevation_t *head = NULL;
    resources_t res1 = {1, 0, 0, 0, 0, 0};
    resources_t res2 = {1, 1, 1, 0, 0, 0};
    resources_t res3 = {2, 0, 1, 0, 2, 0};
    resources_t res4 = {1, 1, 2, 0, 1, 0};
    resources_t res5 = {1, 2, 1, 3, 0, 0};
    resources_t res6 = {1, 2, 3, 0, 1, 0};
    resources_t res7 = {2, 2, 2, 2, 2, 1};

    add_elevation(&head, 2, 1, res1);
    add_elevation(&head, 3, 2, res2);
    add_elevation(&head, 4, 2, res3);
    add_elevation(&head, 5, 4, res4);
    add_elevation(&head, 6, 4, res5);
    add_elevation(&head, 7, 6, res6);
    add_elevation(&head, 8, 6, res7);
    return head;
}
