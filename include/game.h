#ifndef GAME_H
#define GAME_H

#include "basic.h"
#include <SDL.h>

int game_boot();

int game_cut_sprites( SDL_Surface spritesheet );

int game_update();

typedef struct Item{
	char *name;
	SDL_Surface sprite;
} item;

typedef struct Person{
	char *name;
	SDL_Rect body;
	SDL_Rect collidebox;
	int32 health;
	float speed;
	vector vec;
	item inventory[128];
} person;

person Player;

uint32 lastframetime;

#endif /* GAME_H */
