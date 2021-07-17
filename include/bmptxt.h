#ifndef BMPTXT_H
#define BMPTXT_H

#include "basic.h"
#include <SDL.h>

/*Prints text to a surface.
	Surface: the surface to print to.
	text: the ASCII text to print.
	col: the 8x8 column to print to.
	row: the 8x8 row to print to.
*/

void bmp_print(SDL_Surface *Surface, char* text, uint8 col, uint8 row);

void bmp_printxy(SDL_Surface *Surface, char* text, uint16 x, uint16 y);

#endif /* BMPTXT_H */
