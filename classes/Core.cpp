//
//  Core.cpp
//  SLUG
//
//  Created by Steph on 12/15/16.
//
//

#include "Core.hpp"

Core::Core(){
    renderer = NULL;
    screen_scale = 1.0f;
    next_uid = 0;
    components = new IterableHashMap<Component *>(32, NULL);
    printf("New Core! (Should only happen once!)\n");
}

Core::~Core(){
    delete components;
}

Core * Core::getInstance(){
    static Core * GameCore = new Core();
    return GameCore;
}

Component * Core::getComponent(const char * name){
    return components->get(name);
}

Component * Core::removeComponent(const char * name){
    return components->remove(name);
}

void Core::putComponent(const char * name, Component * component){
    components->put(name, component);
}

bool Core::iterate(){
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

long Core::nextUID(){
    return next_uid++;
}

