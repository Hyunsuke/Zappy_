##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

CC	= gcc

SRC	=	src/main.c	\
		src/parsing/parsing.c \
		src/parsing/error.c \
		src/utils/error.c \
		src/utils/garbage_collector.c \
		src/utils/my_strdup.c \
		src/server/server.c \
		src/server/server_usage.c \
		src/server/init.c \
		src/server/handle.c \
		src/server/handle_cmd.c \
		src/server/config.c \
		src/init/generator/generator_map.c \
		src/init/generator/init_map.c \
		src/init/generator/display_map.c \
		src/commands_ia/c_broadcast_txt/broadcast_txt.c \
		src/commands_ia/c_connect_nbr/connect_nbr.c \
		src/commands_ia/c_eject/eject.c \
		src/commands_ia/c_fork/fork.c \
		src/commands_ia/c_forward/forward.c \
		src/commands_ia/c_forward/moove.c \
		src/commands_ia/c_incantation/incantation.c \
		src/commands_ia/c_incantation/start_incantation.c \
		src/commands_ia/c_inventory/inventory.c \
		src/commands_ia/c_left/left.c \
		src/commands_ia/c_look/look.c \
		src/commands_ia/c_look/gestion_coor.c \
		src/commands_ia/c_look/gestion_first_coor.c \
		src/commands_ia/c_look/gestion_str.c \
		src/commands_ia/c_right/right.c \
		src/commands_ia/c_set_obj/set_obj.c \
		src/commands_ia/c_take_obj/take_obj.c \
		src/run_commands/run_commands_ia.c \
		src/utils/players/create_player.c \
		src/utils/players/display_player.c \
		src/utils/players/get_player.c \
		src/utils/players/remove_player.c \
		src/commands_gui/c_msz/msz.c \
		src/commands_gui/c_bct/bct.c \
		src/commands_gui/c_mct/mct.c \
		src/commands_gui/c_tna/tna.c \
		src/commands_gui/c_ppo/ppo.c \
		src/commands_gui/c_plv/plv.c \
		src/commands_gui/c_pin/pin.c \
		src/commands_gui/c_sgt/sgt.c \
		src/commands_gui/c_sst/sst.c \
		src/commands_gui/c_pnw/pnw.c \
		src/commands_gui/c_pex/pex.c \
		src/commands_gui/c_pbc/pbc.c \
		src/commands_gui/c_pic/pic.c \
		src/commands_gui/c_pie/pie.c \
		src/commands_gui/c_pfk/pfk.c \
		src/commands_gui/c_pdr/pdr.c \
		src/commands_gui/c_pgt/pgt.c \
		src/commands_gui/c_pdi/pdi.c \
		src/commands_gui/c_enw/enw.c \
		src/commands_gui/c_ebo/ebo.c \
		src/commands_gui/c_edi/edi.c \
		src/commands_gui/c_seg/seg.c \
		src/commands_gui/c_smg/smg.c \
		src/commands_gui/c_suc/suc.c \
		src/commands_gui/c_sbp/sbp.c \
		src/run_commands/run_commands_gui.c \
		src/run_commands/run_commands_dashboard.c \
		src/utils/team/add_team.c \
		src/utils/team/create_team.c \
		src/utils/team/egg_team.c \
		src/utils/team/get_team.c \
		src/utils/map.c \
		src/utils/init.c \
		src/utils/get_rsc_code.c \
		src/utils/elevation/add_elevation.c \
		src/utils/elevation/get_elevation.c \
		src/utils/elevation/init_elevation.c \
		src/utils/elevation/print_elevation.c \
		src/utils/commands/get_command.c \
		src/utils/commands/add_command.c \
		src/utils/commands/print_command.c \
		src/utils/commands/remove_command.c \
		src/utils/commands/get_tick_for_command.c \
		src/utils/tick.c \
		src/utils/tiredness.c \
		src/utils/signal.c \
		src/utils/split_buffer.c \
		src/utils/progress_incantation/add_progress_incantation.c \
		src/utils/progress_incantation/get_progress_incantation.c \
		src/utils/progress_incantation/remove_progress_incantation.c \
		src/utils/refill.c \
		src/dashboard/send_info.c \
		src/dashboard/get_usage.c \


INCLUDEDIR = ../../include/SERVER/

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-I$(INCLUDEDIR) -W -Wall -Wextra -g -luuid -ljson-c -lm

NAME	=	../../zappy_server

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
