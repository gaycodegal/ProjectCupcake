//
//  Component.cpp
//  SLUG
//
//  Created by Steph on 12/15/16.
//
//

#include "Component.hpp"



Component::Component(long UID, const char * name){
    this->UID = UID;
    unsigned int name_length = std::strlen(name) + 1;
    this->name = new char[name_length];
    std::memcpy(this->name, name, name_length);
}

Component::~Component(){
    delete [] name;
}
