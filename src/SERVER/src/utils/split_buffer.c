/*
** EPITECH PROJECT, 2024
** split_buffer.c
** File description:
** split buffer
*/

#include "all.h"

static int count_lines(const char *buffer)
{
    int lines = 0;

    for (int i = 0; buffer[i]; i++) {
        if (buffer[i] == '\n') {
            lines++;
        }
    }
    return lines;
}

void add_line(char **buffers, int *index, const char *start, int length)
{
    buffers[*index] = my_malloc(length + 1);
    strncpy(buffers[*index], start, length);
    buffers[*index][length] = '\0';
    (*index)++;
}

char **split_buffer(const char *buffer, int *count)
{
    int lines = count_lines(buffer);
    char **buffers = my_malloc((lines + 1) * sizeof(char *));
    const char *start = buffer;
    int index = 0;
    int length = 0;

    for (int i = 0; buffer[i]; i++) {
        if (buffer[i] == '\n') {
            length = &buffer[i] - start;
            add_line(buffers, &index, start, length);
            start = &buffer[i + 1];
        }
    }
    if (start != &buffer[strlen(buffer)]) {
        add_line(buffers, &index, start, strlen(start));
    }
    *count = index;
    return buffers;
}
