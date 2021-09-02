#include "basic.h"
#include "render.h"
#include "console.h"
#include <SDL.h>

typedef struct Console{
    char *name;
    uint8 w;
    uint8 h;
    uint8 x;
    uint8 y;
    SDL_Texture* texture;  
} console;


console consoles[3];
uint8 num_consoles = 0;

int console_new(int w, int h, int x, int y)
{
    if( num_consoles>2 )
    {
        return 0;
    }
    else 
    {
        consoles[num_consoles].w=w;
        consoles[num_consoles].h=h;
        consoles[num_consoles].x=x;
        consoles[num_consoles].y=y;
        consoles[num_consoles].texture = SDL_CreateTextureFromSurface(renderer, SDL_CreateRGBSurface(0,w*8,h*8,32,0,0,0,0));


        num_consoles = num_consoles+1;
        return num_consoles;
    }



    /*
    console this_console;
    this_console.w=w;
    this_console.h=h;
    this_console.x=x;
    this_console.y=y;
    this_console.texture = SDL_CreateTextureFromSurface(renderer, SDL_CreateRGBSurface(0,w*8,h*8,32,0,0,0,0));    
    return true;*/
}

Bool console_print(uint8 console_index, char *text)
{
    return true;
}

Bool bitprint( char *text, uint8 cols, uint8 x, uint8 y)
{
	SDL_Texture *tex;
	uint8 h;
	h = strlen(text) / cols;
	/*tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, cols*8, h*8);
	SDL_Texture *oldtarget;
	oldtarget = SDL_GetRenderTarget(renderer);
	SDL_SetRenderTarget(renderer, tex);*/

	SDL_Rect dstrect;
	dstrect.x=x*8;
	dstrect.y=y*8;
	dstrect.w=8;
	dstrect.h=8;

	uint8 colcount=0;
	int rblitt;
    int i;
	for(i=0;i<strlen(text);i=i+1)
	{
		/*dstrect.x = colcount*8+(x*8);*/
        dstrect.x =colcount*8+(x*8);
		rblitt = SDL_RenderCopy(renderer, ASCII[text[i]+1], NULL, &dstrect);
		colcount = colcount+1;
		if(colcount > cols)
		{
			colcount=0;
			dstrect.y=dstrect.y+8;
		}
	}
	/*SDL_SetRenderTarget(renderer,oldtarget);*/
}