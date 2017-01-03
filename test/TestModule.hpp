//
//  TestModule.hpp
//  SLUG
//
//  Created by Steph on 12/15/16.
//
//

#ifndef TestModule_hpp
#define TestModule_hpp

#include <stdio.h>
#include "Component.hpp"
#include "Core.hpp"

class TestModule: public Component{
private:
    TestModule():Component(Core::getInstance()->nextUID(), "TestModule"){
        Core::getInstance()->putComponent(this->name, this);
    }
public:
    /**
     returns the single instance of this module
     if it does not exist, it will create it.
     */
    static TestModule * getInstance(){
        static TestModule * instance = new TestModule();
        return instance;
    }
    
    /**
     should always run, but will only do so once
     */
    bool should_run(){
        return true;
    }
    
    /**
     run some tests and then remove and
     delete ourself
     */
    void run();
    
    ~TestModule(){
        
    }
};
#endif /* TestModule_hpp */
