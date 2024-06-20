/*
** EPITECH PROJECT, 2024
** get_usage.c
** File description:
** Function
*/

#include "all.h"

static int read_cpu_values(cpu_values_t *cpu_vals)
{
    FILE *fp = fopen("/proc/stat", "r");

    if (fp == NULL) {
        perror("Failed to open /proc/stat");
        return -1;
    }
    if (fscanf(fp, "cpu %ld %ld %ld %ld", &cpu_vals->user,
        &cpu_vals->nice, &cpu_vals->system, &cpu_vals->idle) != 4) {
        perror("Failed to read /proc/stat");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    return 0;
}

void calculate_cpu_usage(struct_t *s, cpu_values_t *cpu_vals)
{
    long total = (cpu_vals->user - cpu_vals->prev_user) +
                (cpu_vals->nice - cpu_vals->prev_nice) +
                (cpu_vals->system - cpu_vals->prev_system) +
                (cpu_vals->idle - cpu_vals->prev_idle);
    long idle_time = cpu_vals->idle - cpu_vals->prev_idle;

    if (total > 0) {
        s->dashboard->cpu_usage = 100 * (total - idle_time) / total;
    } else {
        s->dashboard->cpu_usage = 0;
    }
    cpu_vals->prev_user = cpu_vals->user;
    cpu_vals->prev_nice = cpu_vals->nice;
    cpu_vals->prev_system = cpu_vals->system;
    cpu_vals->prev_idle = cpu_vals->idle;
}

void get_cpu_usage(struct_t *s, cpu_values_t *cpu_vals)
{
    if (read_cpu_values(cpu_vals) == 0) {
        calculate_cpu_usage(s, cpu_vals);
    }
}

void get_ram_usage(struct_t *s)
{
    long total_memory = 0;
    long free_memory = 0;
    FILE *fp = fopen("/proc/meminfo", "r");
    char buffer[256];

    if (fp == NULL)
        return perror("Failed to open /proc/meminfo");
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (sscanf(buffer, "MemTotal: %ld kB", &total_memory) == 1)
            continue;
        if (sscanf(buffer, "MemAvailable: %ld kB", &free_memory) == 1)
            break;
    }
    fclose(fp);
    if (total_memory > 0)
        s->dashboard->ram_usage =
            100 * (total_memory - free_memory) / total_memory;
    else
        s->dashboard->ram_usage = 0;
}

void get_usage(struct_t *s)
{
    static cpu_values_t cpu_vals = {0};

    get_cpu_usage(s, &cpu_vals);
    get_ram_usage(s);
}
