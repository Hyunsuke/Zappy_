##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Makefile
##

NAME = ../../zappy_ai

all: $(NAME)

$(NAME): src/main.py
	@echo '#!/bin/bash' > $(NAME)
	@echo '' >> $(NAME)
	@echo 'python3 src/AI/src/main.py "$$@"' >> $(NAME)
	@chmod +x $(NAME)

clean:
	@rm -rf $src/__pycache__/

fclean: clean
	@rm -f $(NAME)

re: fclean all
