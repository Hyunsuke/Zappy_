/*
** EPITECH PROJECT, 2024
** parsing.h
** File description:
** parsing include
*/

#ifndef PARSING_H
    #define PARSING_H

typedef struct check_s {
    int has_p;
    int has_x;
    int has_y;
    int has_n;
    int has_c;
    int has_f;
    int nb_team;
} check_t;

//Fonction parsing

int parsing(int ac, char **av, struct_t *s);
int check_error(int ac, char **av);

// Generator map
void init_map(struct_t *s);
void generator_map(struct_t *s);
void print_map(struct_t *s);


#endif /* !PARSING_H */
