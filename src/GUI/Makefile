##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Makefile
##

SRCDIR = src
OUTDIR = ../../

SRCDIRS = $(SRCDIR) $(SRCDIR)/core $(SRCDIR)/Collector
SRC_ALL = $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.cpp))
SRC_OBJ = $(SRC_ALL:.cpp=.o)

CPPFLAGS = -W -Wall -Wextra -I../../include/GUI -g -std=c++20

LIBS = -lraylib -lGL -lX11 -lpthread -ldl -lm -lrt

CC = g++ -g

NAME = $(OUTDIR)/zappy_gui

all: $(NAME)

$(NAME): $(SRC_OBJ)
	$(CC) -o $@ $^ $(CPPFLAGS) $(LIBS)

clean:
	rm -f $(SRC_OBJ)


fclean: clean
	rm -f $(NAME)


re: fclean all

.PHONY: all clean fclean re
