#include "basic.h"
#include "game.h"
#include "console.h"
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <gameloop.h>



#pragma region declares
/*Screen dimension constants*/
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
SDL_Rect SCREEN_RECT;

uint8 resolution_multiplier = 1;
Bool GAME_FULLSCREEN = false;

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

SDL_Texture* background = NULL;

SDL_Rect print_rect;
SDL_Rect print_dest_rect;
SDL_Rect rect_16;
SDL_Rect rect_16x32;
SDL_Rect rect_8;
SDL_Rect console_rect_origin;
SDL_Rect console_rect_dest;

uint8 r_i = 0;

SDL_DisplayMode ogmode;

char frametime[2];

uint8 console_indexes[3];


typedef struct{
    SDL_Rect rect;
    coord origin;
    SDL_Texture* texture;
} sprite;

sprite sprarr[256];

/*CP437 ASCII*/
SDL_Texture* ASCII[256];

#pragma endregion

/*Starts up SDL and creates window*/
Bool render_init() 
{
    Bool success = true;
    /*Initialize SDL*/
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError() );
        success = false;
    }
    else {
        /*Create Window*/
        SCREEN_RECT.h = SCREEN_HEIGHT;
        SCREEN_RECT.w = SCREEN_WIDTH;
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
            if (GAME_FULLSCREEN)
            {
            /*SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");*/
			SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
            }
			/**/
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
			
            rect_16x32.x = 0;
            rect_16x32.y = 0;
            rect_16x32.h = 32;
            rect_16x32.w = 16;
            rect_16.x = 0;
            rect_16.y = 0;
            rect_16.h = 16;
            rect_16.w = 16;
            rect_8.x = 0;
            rect_8.y = 0;
            rect_8.h = 8;
            rect_8.w = 8;

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

/*cut text*/
void cut_text(SDL_Surface* image){
    uint8 i;
    uint8 xx;
    uint8 yy;
    SDL_Rect temp_rect;
    temp_rect.x=0;
    temp_rect.y=0;
    temp_rect.w=8;
    temp_rect.h=8;
    SDL_Rect temp_surface_rect;
    temp_surface_rect.x=0;
    temp_surface_rect.y=0;
    temp_surface_rect.w=8;
    temp_surface_rect.h=8;
    for( i=0; i<255; i=i+1 ){
        if( xx==16 ) {
            xx = 0;
            yy = yy+1;
        }
        SDL_Surface* temp_surface;
        temp_surface = SDL_CreateRGBSurface(0,8,8,32,0,0,0,0);
        SDL_BlitSurface(image, &temp_rect, temp_surface, &temp_surface_rect);
        ASCII[i] = SDL_CreateTextureFromSurface(renderer,temp_surface);
        temp_rect.x = xx*8;
        temp_rect.y = yy*8;
        xx = xx+1;
    }
}

/*Loads media*/
Bool render_loadMedia()
{
    Bool success = true;
    SDL_Surface* my_surface;

    console_indexes[0] = console_new(40,30,10,10);
    /*load our ASCII text*/
    cut_text(SDL_LoadBMP("./data/font/red.bmp"));

    background = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("./data/background.bmp"));

    /*my_surface =  SDL_LoadBMP( "./data/RPG_sprites.bmp") ;SDL_LoadBMP( "./data/guy.bmp" );*/
    
    printf("gonna load\n");
    sprarr[0] = cut_sprite(SDL_LoadBMP( "./data/RPG_sprites.bmp" ), 0, 0, 16, 32);
    my_tex = sprarr[0].texture;
    printf("loaded bmp\n");
    
    if( my_tex == NULL )
    {
        printf("Unable to load image. SDL Error: %s\n", SDL_GetError());
        success = false;
        return success;
    }

    SDL_SetTextureBlendMode(my_tex,SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 0);

    SDL_UpdateWindowSurface( gWindow );

    

    console_print(console_indexes[0],"Hello world. This is to test character wrapping");



    return success;
}

int render_frame(){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,background,&SCREEN_RECT,&SCREEN_RECT);
    SDL_RenderCopy(renderer,my_tex,&rect_16x32,&Player.body);

    bitprint("Hello World. This is a pretty incredible thing that I've made. I'm typing this out to see what 40 characters looks like on screen. I wonder how much time it takes to render this many letters every frame.", 40, 10, 70);
    sprintf(frametime,"%d",lastframetime);
    bitprint(&frametime,40,10,0);

    console_render(console_indexes[0]);
    /*SDL_RenderCopy(renderer,ASCII['s'+1],&rect_8,&rect_8);*/
    SDL_RenderPresent(renderer);
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