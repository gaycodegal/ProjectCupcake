//
//  CoreEvent.hpp
//  SLUG
//
//  Created by Steph on 12/16/16.
//
//

#ifndef CoreEvent_hpp
#define CoreEvent_hpp

#include <stdio.h>
#include <cstring>
class CoreEvent{
public:
    /** when the event was recieved or created */
    long timestamp;
    /** the event name */
    char * name;
    /** the thing that sent this */
    void * sender;
    
    /** 
     Any event or message that needs to be sent
     */
    CoreEvent(long timestamp, const char * name):timestamp(timestamp){
        unsigned int name_length = (int)std::strlen(name) + 1;
        this->name = new char[name_length];
        std::memcpy(this->name, name, name_length);
    }
    
    /***/
    virtual ~CoreEvent(){
        delete [] name;
    };
};

#endif /* CoreEvent_hpp */
