#include "basic.h"
#include "game.h"
#include "input.h"
#include <SDL.h>
#include <stdio.h>


const uint8 *keystate;

void input_boot(){
    keystate = SDL_GetKeyboardState(NULL);
}

int input(Bool *gameover) {
    /**gameover = true;*/
    *gameover = false;
    keys.w = false;
    keys.s = false;
    keys.a = false;
    keys.d = false;
    SDL_Event event;

    SDL_PumpEvents();
    while( SDL_PollEvent(&event) != 0 ) {
        if( event.key.keysym.scancode == SDL_SCANCODE_ESCAPE ){
            *gameover = true;
            break;
        }
    }
    if( keystate[SDL_SCANCODE_W] ){
        keys.w = true;
    }
    if( keystate[SDL_SCANCODE_S] ){
        keys.s = true;
    }
    if( keystate[SDL_SCANCODE_A] ){
        keys.a = true;
    }
    if( keystate[SDL_SCANCODE_D] ){
        keys.d = true;
    }
    return 0;
}
