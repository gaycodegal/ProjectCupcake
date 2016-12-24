//
//  EventListener.hpp
//  SLUG
//
//  Created by Steph on 12/16/16.
//
//

#ifndef EventListener_hpp
#define EventListener_hpp

#include <stdio.h>
#include "Component.hpp"
#include "CoreEvent.hpp"

class EventListener: public Component{
public:
    virtual void recieveEvent(const CoreEvent * event){}
};

#endif /* EventListener_hpp */
