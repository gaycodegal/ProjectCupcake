//
//  RandomSquares.hpp
//  SLUG
//
//  Created by Steph on 12/15/16.
//
//

#ifndef RandomSquares_hpp
#define RandomSquares_hpp

#include <stdio.h>
#include "Component.hpp"
#include "Core.hpp"


int randomInt(int min, int max);

void render(SDL_Renderer *renderer, Core * core);

class RandomSquares: public Component{
private:
    RandomSquares():Component(Core::getInstance()->nextUID(), "RandomSquares"){
        Core::getInstance()->putComponent(this->name, this);
    }
public:
    static RandomSquares * getInstance(){
        static RandomSquares * instance = new RandomSquares();
        return instance;
    }
    
    bool should_run(){
        return true;
    }
    
    void run(){
        Core * core = Core::getInstance();
        render(core->renderer, core);
    }
    
    void render(SDL_Renderer *renderer, Core * core);
    
    ~RandomSquares(){
        
    }
};
#endif /* RandomSquares_hpp */
