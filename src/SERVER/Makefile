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
