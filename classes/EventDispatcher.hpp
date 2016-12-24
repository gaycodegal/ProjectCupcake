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
    EventDispatcher():Component(Core::getInstance()->nextUID(), "EventDispatcher"){
        Core::getInstance()->putComponent(this->name, this);
        event_queue_ = new Queue<CoreEvent *>(32, NULL);
        listeners_ = new HashMap<Queue<EventListener *> *>(16, NULL);        
    }
    
    Queue<CoreEvent *> * event_queue_;
    HashMap<Queue<EventListener *> *> * listeners_;
public:
    
    static EventDispatcher * getInstance(){
        static EventDispatcher * dispatcher = new EventDispatcher();
        return dispatcher;
    }
    
    bool should_run(){
        return true;
    }
    
    void addEventListener(const char * event, EventListener * listener){
        Queue<EventListener *> * queue = listeners_->get(event);
        if(queue == NULL){
            queue = new Queue<EventListener *>(32, NULL);
            listeners_->put(event, queue);
        }
        queue->push(listener);
    }
    
    void removeEventListener(const char * event, EventListener * listener){
        Queue<EventListener *> * queue = listeners_->get(event);
        if(queue == NULL)
            return;
        queue->remove(listener);
    }
    
    void postEvent(CoreEvent * event){
        event_queue_->push(event);
    }
    
    void messageListeners(const CoreEvent * event){
        Queue<EventListener *> * queue = listeners_->get(event->name);
        unsigned int size = queue->count();
        EventListener ** listeners = new EventListener*[size];
        EventListener * listener;
        for(unsigned int i = 0; i < size; ++i){
            listener = queue->poll();
            listeners[i] = listener;
            queue->push(listener);
        }
        for(unsigned int i = 0; i < size; ++i){
            listeners[i]->recieveEvent(event);
        }
        delete [] listeners;

    }
    
    void run(){
        SDL_Event event;
        int events_to_handle = 0;
        while (SDL_PollEvent(&event)) {
            printf("hi %i\n",event.type);
            ++events_to_handle;
        }
        printf("EventDispatcher ran %i events\n",events_to_handle);
    }
    ~EventDispatcher(){
        event_queue_->drain();
        delete event_queue_;
        listeners_->drain();
        delete listeners_;
    }
};

#endif /* EventDispatcher_hpp */
