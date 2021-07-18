SRC_DIR := ./src

#OBJS
#OBJS = $(wildcard $(SRC_DIR))/*.c
#OBJS = ./src/main.c ./src/game.c ./src/gameloop.c ./src/input.c ./src/render.c ./src/update.c
OBJS = ./src/hack.c

CC = gcc

INCLUDE_PATHS = -I./include

LIBRARY_PATHS = -L./lib

COMPILER_FLAGS = -std=c89 -w

#LINKER_FLAGS = -lSDL2_ttf

OBJ_NAME = r

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) -Wall $(COMPILER_FLAGS) $(LINKER_FLAGS) `sdl2-config --cflags --libs` -g -o $(OBJ_NAME) 2> err.txt
