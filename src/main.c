#include "basic.h" /*C89 bool, type nicknames*/
#include "gameloop.h"
#include "render.h"

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*#undef main /*SDL2 redefines main which caused an error unless I undeffed it*/

int main(int argc, char *argv[]) {
    render_controller();
    
    playgame();

    render_close();
    return 0;
}
