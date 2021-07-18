#include "basic.h"
#include "game.h"
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>



#pragma region declares
/*Screen dimension constants*/
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;
uint8 resolution_multiplier = 3;

/*the window we'll be rendering to*/
SDL_Window* gWindow = NULL;

/*the surface contained by the window*/
SDL_Surface* gScreenSurface = NULL;

/*the image we will load and show on the screen*/
SDL_Surface* gHelloWorld = NULL;

SDL_Renderer* renderer;

SDL_Texture* my_tex;
SDL_Texture* spritesheet_tex;  /*my sprite sheet*/
SDL_Texture* print_tex = NULL;
SDL_Texture* console_tex = NULL;

SDL_Rect print_rect;
SDL_Rect print_dest_rect;
SDL_Rect rect_16;
SDL_Rect console_rect_origin;
SDL_Rect console_rect_dest;

uint8 r_i = 0;

SDL_DisplayMode ogmode;

struct printer{
    SDL_Rect srcrect;
    SDL_Rect destrect;
    SDL_Texture* texture;
};

struct printer printarr[20];
uint8 printcounter;

typedef struct{
    SDL_Rect rect;
    coord origin;
    SDL_Texture* texture;
} sprite;

sprite sprarr[256];

#pragma endregion

/*Starts up SDL and creates window*/
Bool render_init() 
{
    Bool success = true;
    printcounter = 0;
    /*Initialize SDL*/
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError() );
        success = false;
    }
    else {
        /*Create Window*/
        gWindow = SDL_CreateWindow( "Rok", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH*resolution_multiplier, SCREEN_HEIGHT*resolution_multiplier, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
        if( gWindow == NULL )
        {
            printf( "Window could not be created. SDL_Error: %s\n",SDL_GetError() );
            success = false;
        }
        else {
            /*create renderer*/
            renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

            /*get window surface*/
            gScreenSurface = SDL_GetWindowSurface( gWindow );

			/*get desktop display mode*/
			SDL_GetDesktopDisplayMode(0, &ogmode);

			/*this makes it so game always plays in one resolution*/
			SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

			SDL_RenderSetScale(renderer, resolution_multiplier, resolution_multiplier);
            /*set fullscreen*/
			/*SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);*/

			/**/
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
			
            rect_16.x = 0;
            rect_16.y = 0;
            rect_16.h = 32;
            rect_16.w = 16;
        

        }
    }
    return success;
}

/*cuts spritesheet*/
sprite cut_sprite(SDL_Surface* surface, int x, int y, int w, int h){
    sprite spr;
    SDL_Surface* temp_surface;
    temp_surface = SDL_CreateRGBSurface(0,w,h,32,0,0,0,0);
    SDL_Rect temp_src_rect;
    temp_src_rect.x = x;
    temp_src_rect.y = y;
    temp_src_rect.w = w;
    temp_src_rect.h = h; 

    SDL_Rect temp_dest_rect;
    temp_dest_rect.x = 0;
    temp_dest_rect.y = 0;
    temp_dest_rect.w = w;
    temp_dest_rect.h = h;
    SDL_BlitSurface(surface,&temp_src_rect,temp_surface,&temp_dest_rect);
    uint32 tcolorkey = SDL_MapRGB(temp_surface->format,0,0,0);
    SDL_SetColorKey(temp_surface, SDL_TRUE, tcolorkey);

    spr.texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
    SDL_GetClipRect(temp_surface,&spr.rect);
    SDL_SetTextureBlendMode(spr.texture,SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(temp_surface);
    return spr;
}


/*Loads media*/
Bool render_loadMedia()
{
    Bool success = true;
    SDL_Surface* my_surface;


    /*my_surface =  SDL_LoadBMP( "./data/RPG_sprites.bmp") ;SDL_LoadBMP( "./data/guy.bmp" );*/
    
    printf("gonna load\n");
    sprarr[0].texture = SDL_LoadBMP( "./data/RPG_sprites.bmp" );
    my_surface = sprarr[0].texture;
    printf("loaded bmp\n");
    
    if( my_surface == NULL )
    {
        printf("Unable to load image. SDL Error: %s\n", SDL_GetError());
        success = false;
        return success;
    }


    uint32 colorkey = SDL_MapRGB(my_surface->format,255,255,255);
    SDL_SetColorKey(my_surface, SDL_TRUE, colorkey);
    my_tex = SDL_CreateTextureFromSurface(renderer, my_surface);
    SDL_SetTextureBlendMode(my_tex,SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 0);
    SDL_FreeSurface(my_surface);

    my_surface = NULL;
    my_surface = SDL_LoadBMP("./data/RPG_sprites.bmp");
    if( my_surface == NULL )
    {
        printf("unable to load RPG_sprites");
        success = false;
        return success;
    }
    SDL_SetColorKey(my_surface, SDL_TRUE, colorkey);

    sprite spr;
    spr = cut_sprite(my_surface,16,0,16,32);

    spritesheet_tex = spr.texture;
    /*this is where we should cut into sprites*/
    SDL_FreeSurface(my_surface);


    SDL_UpdateWindowSurface( gWindow );

    return success;
}

int render_frame(){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,my_tex,&rect_16,&Player.body);
    SDL_RenderCopy(renderer,console_tex,&console_rect_origin,&console_rect_dest);
    SDL_RenderCopy(renderer,print_tex,&print_rect,&print_dest_rect);
    /*SDL_RenderCopy(renderer,spritesheet_tex,&rect_16,&Player.body);*/

    uint8 i;
    for( i=0; i<printcounter; ++i ){
        SDL_RenderCopy(renderer,printarr[i].texture,&printarr[i].srcrect,&printarr[i].destrect);
        SDL_DestroyTexture(printarr[i].texture);
    }
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(print_tex);
    SDL_DestroyTexture(console_tex);
    printcounter = 0;
    return 0;
}

void render_close(){
	SDL_SetWindowSize(gWindow, ogmode.w, ogmode.h);
}

int render_controller(){
    Bool success = 2;
    if(render_init()==false){
        success = success - 1;
    }
    if(render_loadMedia()==false){
        success = success - 1;
    }
    printf("%x of 2 loading successes\n",success);
    return success;
}


void render_print(char *text, int32 x, int32 y){
}

void render_printer(char *text, int32 x, int32 y) {
}

void render_print_debug(){
}

