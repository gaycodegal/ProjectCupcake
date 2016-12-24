//
//  global_init.cpp
//  SLUG
//
//  Created by Steph on 12/15/16.
//
//

#include "global_init.hpp"


int global_init(){
    /* this *HAS* to come first - it init's core */
    Core * GameCore = Core::getInstance();
    /* 
     this for instance, inits
     Event Dispatcher, and relies on core.
     Order of init for Singleton components
     will determine order of calling within Core.
     */
    EventDispatcher::getInstance();
    RandomSquares::getInstance();
    SDL_Window *window;
    
    SDL_Rect screenBounds;
    SDL_Rect screenPoints;
    SDL_Renderer *globalRenderer;
    bool isRetina = true;
    float RETINA_FACTOR = 1;

    
    /* initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL\n");
        return 1;
    }
    
    /* initialize TTF */
    if( TTF_Init() == -1 ){
        printf("Could not initialize SDL\n");
        return 1;
    }
    
    /* seed random number generator */
    srand((uint)time(NULL));
    
    /* get window bounds from sys */
    if (SDL_GetDisplayBounds(0, &screenBounds) != 0) {
        SDL_Log("SDL_GetDisplayBounds failed: %s", SDL_GetError());
        return 1;
    }
    
    
    Uint32 initopts = SDL_WINDOW_OPENGL;
    if(isRetina)
        initopts |= SDL_WINDOW_ALLOW_HIGHDPI;
    
    
    /* create window and renderer */
    window =
    SDL_CreateWindow(NULL, 0, 0, screenBounds.w, screenBounds.h,
                     initopts);
    
    
    
    
    if (!window) {
        printf("Could not initialize Window\n");
        return 1;
    }
    
    globalRenderer = SDL_CreateRenderer(window, -1, 0);
    if (!globalRenderer) {
        printf("Could not create renderer\n");
        return 1;
    }
    GameCore->renderer = globalRenderer;
    
    
    if(isRetina){
        int a = 0, b = 0;
        isRetina = false;
        SDL_GetRendererOutputSize(globalRenderer, &a, &b);
        if(a){
            RETINA_FACTOR = a/screenBounds.w;
            isRetina = true;
        }
    }
    GameCore->screen_scale = RETINA_FACTOR;
    screenPoints.x = 0;
    screenPoints.y = 0;
    screenPoints.w = screenBounds.w;
    screenPoints.h = screenBounds.h;
    screenBounds.w *= RETINA_FACTOR;
    screenBounds.h *= RETINA_FACTOR;
    GameCore->screen_rect = screenBounds;
    GameCore->screen_points = screenPoints;
    return 0;
}
