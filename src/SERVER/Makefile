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
		src/server/print.c \
		src/server/init.c \
		src/server/handle.c \
		src/server/handle_cmd.c \
		src/server/config.c \
		src/init/generator/generator_map.c \
		src/init/generator/init_map.c \
		src/init/generator/display_map.c \
		src/run_commands/run_commands.c \
		src/commands/c_broadcast_txt/broadcast_txt.c \
		src/commands/c_connect_nbr/connect_nbr.c \
		src/commands/c_eject/eject.c \
		src/commands/c_fork/fork.c \
		src/commands/c_forward/forward.c \
		src/commands/c_incantation/incantation.c \
		src/commands/c_inventory/inventory.c \
		src/commands/c_left/left.c \
		src/commands/c_look/look.c \
		src/commands/c_right/right.c \
		src/commands/c_set_obj/set_obj.c \
		src/commands/c_take_obj/take_obj.c \
		src/run_commands/run_commands.c \
		src/utils/players/create_player.c \
		src/utils/players/display_player.c \
		src/utils/players/get_player.c \

INCLUDEDIR = ../../include/SERVER/

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-I$(INCLUDEDIR) -W -Wall -Wextra -g -luuid

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
