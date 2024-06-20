##
## EPITECH PROJECT, 2024
## delivery
## File description:
## Makefile
##

all:
	make -C src/AI/
	make -C src/GUI/
	make -C src/SERVER/

AI:
	make -C src/AI/

GUI:
	make -C src/GUI/

SERVER:
	make -C src/SERVER/

clean:
	make -C src/AI/ clean
	make -C src/GUI/ clean
	make -C src/SERVER/ clean

fclean: clean
	make -C src/AI/ fclean
	make -C src/GUI/ fclean
	make -C src/SERVER/ fclean

re: fclean all

.PHONY: all clean fclean re AI GUI SERVER
