#ifndef RENDER_H
#define RENDER_H

#include "basic.h"
#include <SDL.h>

/*the main function*/
int render_frame();

/*Starts up SDL and creates window*/
Bool render_init();

/*Loads media*/
Bool render_loadMedia();

void render_print(char *text, int32 x, int32 y);
void render_printer(char *text, int32 x, int32 y);
void render_print_debug();

/*Frees media and shuts down SDL*/
void render_close();

int render_controller();

SDL_Surface *render_ScaleSurface(SDL_Surface *Surface, uint16 width, uint16 height);
#endif /* RENDER_H */
