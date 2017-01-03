//
//  EventDispatcherComponent.cpp
//  SLUG
//
//  Created by Steph on 12/15/16.
//
//

#include "EventDispatcher.hpp"



EventDispatcher * EventDispatcher::getInstance(){
    static EventDispatcher * dispatcher = new EventDispatcher();
    return dispatcher;
}

bool EventDispatcher::should_run(){
    return true;
}

void EventDispatcher::addEventListener(const char * event, EventListener * listener){
    Queue<EventListener *> * queue = listeners_->get(event);
    if(queue == NULL){
        queue = new Queue<EventListener *>(32, NULL);
        listeners_->put(event, queue);
    }
    queue->push(listener);
}

void EventDispatcher::removeEventListener(const char * event, EventListener * listener){
    Queue<EventListener *> * queue = listeners_->get(event);
    if(queue == NULL)
        return;
    queue->remove(listener);
}

void EventDispatcher::messageListeners(const CoreEvent * event){
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

void EventDispatcher::run(){
    SDL_Event event;
    int events_to_handle = 0;
    while (SDL_PollEvent(&event)) {
        printf("hi %i\n",event.type);
        ++events_to_handle;
    }
    printf("EventDispatcher ran %i events\n",events_to_handle);
}

EventDispatcher::~EventDispatcher(){
    listeners_->drain();
    delete listeners_;
}
