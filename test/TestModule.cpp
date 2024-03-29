//
//  RandomSquares.cpp
//  SLUG
//
//  Created by Steph on 12/15/16.
//
//

#include "TestModule.hpp"
#include "test_queue.hpp"
#include "test_hash.hpp"
#include "test_iter_hash.hpp"
#include "test_bson.hpp"


void TestModule::run(){
    printf("vvv TESTING\n");
    test_queue();
    test_hash();
    test_iter_hash();
    test_bson();
    Core * core = Core::getInstance();
    
    if(core->removeComponent("TestModule") == NULL)
        printf("FAILED To REMOVE TestModule!\n");
    
    printf("^^^ If nothing appears above, all tests passed!\n");
    
    //anytime we remove a component we're no longer using make sure it is deleted.
    delete this;
}
