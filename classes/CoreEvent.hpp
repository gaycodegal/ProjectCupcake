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
    long timestamp;
    char * name;
    void * sender;
    CoreEvent(long timestamp, const char * name):timestamp(timestamp){
        unsigned int name_length = std::strlen(name) + 1;
        this->name = new char[name_length];
        std::memcpy(this->name, name, name_length);
    }
    virtual ~CoreEvent(){
        delete [] name;
    };
};

#endif /* CoreEvent_hpp */
