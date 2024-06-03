/*
** EPITECH PROJECT, 2024
** B4 - Network Programming
** File description:
** commands.c
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "struct.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// COMMANDS IA ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int c_forward(struct_t *s, int fd);
int c_right(struct_t *s, int fd);
int c_left(struct_t *s, int fd);
int c_look(struct_t *s, int fd);
int c_inventory(struct_t *s, int fd);
int c_broadcast_txt(struct_t *s, int fd);
int c_connect_nbr(struct_t *s, int fd);
int c_fork(struct_t *s, int fd);
int c_eject(struct_t *s, int fd);
int c_take_obj(struct_t *s, int fd);
int c_set_obj(struct_t *s, int fd);
int c_incantation(struct_t *s, int fd);


///////////////////////////////////////////////////////////////////////////////
/////////////////////////// COMMANDS GUI///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int c_msz(struct_t *s, char *buffer);
int c_bct(struct_t *s, char *buffer);
int c_mct(struct_t *s, char *buffer);
int c_tna(struct_t *s, char *buffer);
int c_ppo(struct_t *s, char *buffer);
int c_plv(struct_t *s, char *buffer);
int c_pin(struct_t *s, char *buffer);
int c_sgt(struct_t *s, char *buffer);
int c_sst(struct_t *s, char *buffer);

int c_pnw(struct_t *s);
int c_pex(struct_t *s, int id_player);
int c_pbc(struct_t *s, int id_player, char *name_team);
int c_pic(struct_t *s);
int c_pie(struct_t *s, int x, int y, int incantation_result);
int c_pfk(struct_t *s, int id_player);
int c_pdr(struct_t *s);
int c_pgt(struct_t *s);
int c_pdi(struct_t *s);
int c_enw(struct_t *s);
int c_ebo(struct_t *s);
int c_edi(struct_t *s);
int c_seg(struct_t *s);
int c_smg(struct_t *s);
int c_suc(struct_t *s);
int c_sbp(struct_t *s);


///////////////////////////////////////////////////////////////////////////////
/////////////////////// STRUCT ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

typedef struct {
    char *command;
    int (*func)(struct_t *s, char *buffer);
    } command_struct_gui_t;
    typedef struct {
    char *command;
    int (*func)(struct_t *s, int fd);
} command_struct_ia_t;

#endif /* !COMMANDS_H_ */