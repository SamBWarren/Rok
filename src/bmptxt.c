#include "basic.h"
#include <SDL.h>

SDL_Surface* font;
SDL_Surface* character[256];

uint8 fontwidth;
uint8 fontheight;

void bmp_print(SDL_Surface* Surface, char* text, uint8 col, uint8 row)
{
	
}

Bool cut_font()
{
	Bool success = true;
		/*
		SDL_Rect temp_src_rect;
		temp_src_rect.x=0;
		temp_src_rect.y=0;
		temp_src_rect.w=fontwidth;
		temp_src_rect.h=fontheight;

		SDL_Rect temp_dest_rect;
		temp_dest_rect.x=0;
    	temp_dest_rect.y = 0;
    	temp_dest_rect.w = fontwidth;
    	temp_dest_rect.h = fondheight;
		
		uint16 i;
		while i<255
		{
			SDL_BlitSurface(surface,&temp_src_rect,temp_surface)
		}
		*/
	return success;
}

Bool load_font(char* path)
{
	Bool success = true;
	font = SDL_LoadBMP(path);
	if( font == NULL )
	{
		printf("Unable to load font. SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	return success;
}
