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

char **split_buffer(const char *buffer, int *count)
{
    int lines = count_lines(buffer);
    char **buffers = my_malloc((lines + 1) * sizeof(char*));
    const char *start = buffer;
    int index = 0;
    int length = 0;

    for (int i = 0; buffer[i]; i++) {
        if (buffer[i] == '\n') {
            length = &buffer[i] - start;
            buffers[index] = my_malloc(length + 1);
            strncpy(buffers[index], start, length);
            buffers[index][length] = '\0';
            start = &buffer[i + 1];
            index++;
        }
    }
    if (start != &buffer[strlen(buffer)]) {
        buffers[index] = my_strdup(start);
        index++;
    }
    *count = index;
    return buffers;
}
