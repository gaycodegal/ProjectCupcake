//
//  RandomSquares.cpp
//  SLUG
//
//  Created by Steph on 12/15/16.
//
//

#include "RandomSquares.hpp"

/**
 returns a random number in
 a range. rand() % x is not that good
 of a random, but it's fine for this.
 */
int randomInt(int min, int max)
{
    return min + rand() % (max - min + 1);
}

/**
 draws some random squares onto the renderer provided
 */
void RandomSquares::render(SDL_Renderer *renderer, Core * core)
{
    SDL_Rect screen_rect = core->screen_rect;
    
    Uint8 r, g, b;
    
    /* Clear the screen */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    /*  Come up with a random rectangle */
    SDL_Rect rect;
    rect.w = randomInt(64, 128);
    rect.h = randomInt(64, 128);
    rect.x = randomInt(0, screen_rect.w - rect.w);
    rect.y = randomInt(0, screen_rect.h - rect.h);
    
    /* Come up with a random color */
    r = randomInt(50, 255);
    g = randomInt(50, 255);
    b = randomInt(50, 255);
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    
    /*  Fill the rectangle in the color */
    SDL_RenderFillRect(renderer, &rect);
    
}
