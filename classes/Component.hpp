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

/**
 A component can be anything that is unique - a button on a page,
 an input management system - anything that can and should be given
 a name. It makes it easier to handle these objects and request them
 by name.
 
 Abstract, but you can implement the component class as if it weren't
 in case you need a non-functioning instance.
 */
class Component{
public:
    /** a unique id associated with each component */
    long UID;
    /** a human-friendly name associated with the component */
    char * name;
    Component(long UID, const char * name);
    virtual ~Component();
    /** 
     asks the question does this component need to do work?
     that work is nebulously defined, and generally specific
     to the subclass
     */
    virtual bool should_run(){
        return false;
    };
    /**
     does work if nesc.
     */
    virtual void run(){};
};



#endif /* Component_hpp */
