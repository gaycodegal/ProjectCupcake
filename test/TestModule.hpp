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
    
    static TestModule * getInstance(){
        static TestModule * instance = new TestModule();
        return instance;
    }
    
    bool should_run(){
        return true;
    }
    
    void run();
    
    ~TestModule(){
        
    }
};
#endif /* TestModule_hpp */
