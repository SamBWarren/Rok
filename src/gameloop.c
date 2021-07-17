#include "game.h"
#include "input.h"
#include "render.h"
#include "basic.h"

#include <SDL.h>

#define TICK_INTERVAL 16

Bool gameover = false;
Bool loadmedia = true;

uint32 NOW;
uint32 NEXT;
uint32 lastframetime;

uint32 time_left()
{
    NOW = SDL_GetTicks();
    if(NEXT<=NOW)
    {
        return 0;
    }
    else{
        return NEXT - NOW;
    }
}

int playgame()
{
    input_boot();
    game_boot();
    NEXT = SDL_GetTicks() + TICK_INTERVAL;
    while(true) {

        input(&gameover);               /*read inputs*/
        game_update();                   /*update gamestate*/
        render_frame();                 /*draw frame*/

        lastframetime = time_left();
        SDL_Delay(lastframetime);         /*wait*/
        NEXT += TICK_INTERVAL;

        if (gameover == true) {
            break;
        }
    }
    return 0;
}