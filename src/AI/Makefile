##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Makefile
##

# Définition des variables
SOURCE = src/main.py
COPIE = zappy_ai.py
DESTINATION = ../../
DEST_FILE = $(DESTINATION)/$(COPIE)

all: copy move

copy:
	@echo "Copie de $(SOURCE) vers $(COPIE)"
	@cp $(SOURCE) $(COPIE)

move: copy
	@echo "Déplacement de $(COPIE) vers $(DESTINATION)"
	@mv $(COPIE) $(DESTINATION)
	@chmod +x $(DEST_FILE)

clean:
	@echo "Nettoyage des fichiers générés"
	@rm -f $(DESTINATION)/$(COPIE)

.PHONY: all copy move clean
