/*
** EPITECH PROJECT, 2024
** gorbage_collector.c
** File description:
** Function my_malloc and my_free
*/

#include "all.h"

garbage_collector_t *get_struct_collector(void)
{
    static garbage_collector_t gc = { .head = NULL };

    return &gc;
}

void *my_malloc(size_t size_malloc)
{
    void *pointer;
    GCNode_t *node;
    garbage_collector_t *gc = get_struct_collector();

    pointer = malloc(size_malloc);
    node = malloc(sizeof(GCNode_t));
    if (pointer == NULL || node == NULL) {
        dprintf(2, "Error allocating memory (my_malloc)\n");
        exit(84);
    }
    node->pointer = pointer;
    node->next = gc->head;
    gc->head = node;
    return pointer;
}

void full_free(void)
{
    garbage_collector_t *gc = get_struct_collector();
    GCNode_t *node = gc->head;
    GCNode_t *temp;

    while (node != NULL) {
        temp = node;
        node = node->next;
        free(temp->pointer);
        free(temp);
    }
    gc->head = NULL;
}

void *my_realloc(void *ptr, size_t size)
{
    void *newPtr;
    GCNode_t *node;
    garbage_collector_t *gc = get_struct_collector();

    if (ptr == NULL)
        return my_malloc(size);
    newPtr = realloc(ptr, size);
    if (newPtr == NULL)
        return NULL;
    node = gc->head;
    while (node != NULL) {
        if (node->pointer == ptr) {
            node->pointer = newPtr;
            break;
        }
        node = node->next;
    }
    return newPtr;
}

void my_free(void *ptr)
{
    garbage_collector_t *gc = get_struct_collector();
    GCNode_t **indirect = &gc->head;
    GCNode_t *temp;

    if (ptr == NULL)
        return;
    while (*indirect != NULL) {
        if ((*indirect)->pointer == ptr) {
            temp = *indirect;
            *indirect = temp->next;
            free(temp->pointer);
            free(temp);
            return;
        }
        indirect = &(*indirect)->next;
    }
}
