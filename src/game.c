#include "basic.h" /*C89 bool, type nicknames*/
#include "gameloop.h"
#include "render.h"
#include "input.h"
#include "game.h"

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* this is the main game */
/* it holds all the structs */

const float BASE_SPEED = 3;

int game_boot()
{
    Player.body.x=16;
    Player.body.y=32;
    Player.body.w=16;
    Player.body.h=32;
    Player.speed = 1;
    Player.name = "Sam";
    return 0;
    /*samparse();*/
}

int game_cut_sprites( SDL_Surface spritesheet )
{
    return 0;
}

vector dir_vec(){
    vector vec;
    vec.b.y = 0;
    vec.b.x = 0;
    vec.a.x = 0;
    vec.a.y = 0;
    if( keys.w == true ) {
        vec.b.y -= 1;
    }
    if( keys.s == true ) {
        vec.b.y += 1;
    }
    if( keys.a == true ) {
        vec.b.x -= 1;
    }
    if( keys.d == true ) {
        vec.b.x += 1;
    }
    return vec;
}

int game_update()
{
    /*get an (x,y) coordinate for current direction*/
    Player.vec = dir_vec();
    uint8 diag = 0;
    if( Player.vec.b.x != 0 ){
        if( Player.vec.b.y != 0 ){
            diag = 1;
        }
    }
    if( !diag ){
        Player.body.x = Player.body.x + (Player.vec.b.x*(BASE_SPEED+Player.speed));
        Player.body.y = Player.body.y + (Player.vec.b.y*(BASE_SPEED+Player.speed));
    } else {
        Player.body.x = Player.body.x + ((Player.vec.b.x*(BASE_SPEED+Player.speed))*0.75);
        Player.body.y = Player.body.y + ((Player.vec.b.y*(BASE_SPEED+Player.speed))*0.75);
    }
    char buffer[50];
    sprintf(buffer,"%s",Player.name);
    /*render_printer(buffer,Player.body.x,Player.body.y-8);*/
    /*render_printer("testing",0,0);*/
    /*render_print_debug();*/

    return 0;
}

