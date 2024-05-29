##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

CC	= gcc

SRC	=	src/main.c	\
		src/parsing/parsing.c \
		src/utils/error.c \
		src/utils/gorbage_collector.c \
		src/utils/my_strdup.c \
		src/init/generator/generator_map.c \
		src/init/generator/init_map.c \
		src/init/generator/display_map.c \

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
