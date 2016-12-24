//
//  Core.hpp
//  SLUG
//
//  Created by Steph on 12/15/16.
//
//

#ifndef Core_hpp
#define Core_hpp

#include <stdio.h>
#include "SDL.h"
#include "IterableHashmap.hpp"
#include "Component.hpp"

class Core{
private:
    Core();
    long next_uid;
    IterableHashMap<Component *> * components;
public:
    
    /**
     The global renderer. Live.
     */
    SDL_Renderer * renderer;
    
    /**
     The screen's size if it were at 1.0 scale
     */
    SDL_Rect screen_points;
    
    /**
     The actual rect of the screen in pixels.
     */
    SDL_Rect screen_rect;
    
    /**
     The scale of the screen. Retina is 2.0 for iphone 6,
     3.0 for some iphone 7. Possibly a wide range of values.
     */
    float screen_scale;
    
    /**
     Called solely by main, as there can only be one 
     Core at any time.
     */
    ~Core();
    
    /**
     Gets the instance of Core.
     @return GameCore the instance of Core.
     */
    static Core * getInstance();
    
    Component * getComponent(const char * name){
        return components->get(name);
    }
    
    void putComponent(const char * name, Component * component){
        components->put(name, component);
    }
    
    bool iterate(){
        int length = components->count();
        for(int i = 0; i < length; ++i){
            Component * c = components->get(i);
            if(c->should_run())
                c->run();
        }
        
        /* update screen, allow new events to appear */
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        return true;
    }
    
    long nextUID();
    
    /**
     Just a test method.
     */
    void test(){
        printf("You have successfully tested!\n");
    }
};

#endif /* Core_hpp */
