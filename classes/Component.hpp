//
//  Component.hpp
//  SLUG
//
//  Created by Steph on 12/15/16.
//
//

#ifndef Component_hpp
#define Component_hpp

#include <stdio.h>
#include <cstring>

class Component{
public:
    long UID;
    char * name;
    Component(long UID, const char * name);
    virtual ~Component();
    virtual bool should_run(){
        return false;
    };
    virtual void run(){};
};



#endif /* Component_hpp */
