##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Makefile
##

SRCDIR = src

SRCDIRS = $(SRCDIR)
SRC_ALL = $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.cpp))
SRC_OBJ = $(SRC_ALL:.cpp=.o)

CPPFLAGS = -W -Wall -Wextra -Iinclude -g -std=c++20

CC = g++ -g

NAME = zappy_gui

all: $(NAME)

$(NAME): $(SRC_OBJ)
	$(CC) -o $@ $^ $(CPPFLAGS)

clean:
	rm -f $(SRC_OBJ)


fclean: clean
	rm -f $(NAME)


re: fclean all

.PHONY: all clean fclean re
