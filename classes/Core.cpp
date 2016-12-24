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
    components = new IterableHashMap<Component *>();
    printf("New Core! (Should only happen once!)\n");
}

Core::~Core(){
    
}

Core * Core::getInstance(){
    static Core * GameCore = new Core();
    return GameCore;
}

long Core::nextUID(){
    return next_uid++;
}
