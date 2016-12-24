/**
 issues, fix events not being caugt because the app is asleep.
 make a redraw in square for animation purposes that don't kill the cpu
 enable low cpu mode in which we don't do a lot of the animations
 that appear in rects.
 undo button & history
 file systems hash
 saving / loading from documents
 */

#include "SDL.h"
#include "SDL_ttf.h"
#include "Core.hpp"
#include <ctime>
#include "global_init.hpp"

int main(int argc, char *argv[])
{
    global_init();
    
    Core * core = Core::getInstance();
    while(core->iterate());
    
    /* shutdown SDL */
    SDL_Quit();
    delete core;
    return 0;
}




