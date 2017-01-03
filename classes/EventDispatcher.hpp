//
//  EventDispatcher.hpp
//  SLUG
//
//  Created by Steph on 12/15/16.
//
//

#ifndef EventDispatcher_hpp
#define EventDispatcher_hpp

#include <stdio.h>
#include "Component.hpp"
#include "Core.hpp"
#include "CoreEvent.hpp"
#include "EventListener.hpp"
#include "Queue.hpp"

class EventDispatcher: public Component{
private:
    
    /***/
    EventDispatcher():Component(Core::getInstance()->nextUID(), "EventDispatcher"){
        Core::getInstance()->putComponent(this->name, this);
        listeners_ = new HashMap<Queue<EventListener *> *>(16, NULL);        
    }
    
    /**
     the listeners by event name
     */
    HashMap<Queue<EventListener *> *> * listeners_;
public:
    
    /**
     get the single instance of this
     */
    static EventDispatcher * getInstance();
    
    /**
     events are always important
     */
    bool should_run();
    
    /**
     add a listener for a specific event
     */
    void addEventListener(const char * event, EventListener * listener);
    
    /** 
     remove a listener for a specific event
     */
    void removeEventListener(const char * event, EventListener * listener);
    
    /**
     send a message to the listeners for some event
     */
    void messageListeners(const CoreEvent * event);
    
    /**
     handle touch inputs,
     keyboard events,
     and clicks.
     
     todo: we'll have to message the listeners here 
     efficiently ourselves. calling message listeners
     each time might be problematic?
     */
    void run();

    /**
     deletes only the hashtable, not the listeners themselves.
     */
    ~EventDispatcher();
};

#endif /* EventDispatcher_hpp */
