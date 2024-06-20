##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Makefile
##

SRCDIR = src
OUTDIR = ../../

SRC = 	$(SRCDIR)/main.cpp \
        $(SRCDIR)/Collector/AnimationCollector.cpp \
        $(SRCDIR)/Collector/ModelCollector.cpp \
        $(SRCDIR)/Collector/TextureCollector.cpp \
        $(SRCDIR)/core/CameraController.cpp \
        $(SRCDIR)/core/Egg.cpp \
        $(SRCDIR)/core/Game.cpp \
        $(SRCDIR)/core/GameException.cpp \
        $(SRCDIR)/core/GameSocket/GameSocket.cpp \
        $(SRCDIR)/core/GameSocket/ReactionFunc.cpp \
        $(SRCDIR)/core/Island.cpp \
        $(SRCDIR)/core/Map.cpp \
        $(SRCDIR)/core/ModelLoader.cpp \
        $(SRCDIR)/core/Object3D.cpp \
        $(SRCDIR)/core/Player/Player.cpp \
        $(SRCDIR)/Manager/CameraManager.cpp \
        $(SRCDIR)/Manager/ChatManager.cpp \
        $(SRCDIR)/Manager/RayManager.cpp \
        $(SRCDIR)/Manager/ShaderManager.cpp \
        $(SRCDIR)/Manager/UIManager.cpp \
        $(SRCDIR)/Menu/Button.cpp \
        $(SRCDIR)/Menu/menu.cpp \
        $(SRCDIR)/Menu/endMenu.cpp \
        $(SRCDIR)/Menu/loading.cpp \
        $(SRCDIR)/Menu/LoadingMenu.cpp \
        $(SRCDIR)/Settings/settings.cpp \
        $(SRCDIR)/Sky/Sky.cpp \
        $(SRCDIR)/Socket/SocketManager.cpp \
        $(SRCDIR)/Utils/utils.cpp \
        $(SRCDIR)/Wrapper/Raylib/RLModel.cpp \
        $(SRCDIR)/Wrapper/Raylib/RLRay.cpp \
        $(SRCDIR)/Wrapper/Raylib/RLShader.cpp \
        $(SRCDIR)/Wrapper/Raylib/RLText.cpp \
        $(SRCDIR)/Wrapper/Raylib/RLWindow.cpp \
        $(SRCDIR)/Wrapper/Raylib/RLAnimation.cpp \
        $(SRCDIR)/Wrapper/SocketWrapper.cpp \

SRC_OBJ = $(SRC:.cpp=.o)

CPPFLAGS = -W -Wall -Wextra -I../../include/GUI -std=c++20 -g

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
