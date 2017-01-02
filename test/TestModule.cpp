//
//  RandomSquares.cpp
//  SLUG
//
//  Created by Steph on 12/15/16.
//
//

#include "TestModule.hpp"
#include "test_queue.cpp"
#include "test_hash.hpp"
#include "test_iter_hash.hpp"


void TestModule::run(){
    printf("vvv TESTING\n");
    test_queue();
    test_hash();
    test_iter_hash();
    Core * core = Core::getInstance();
    
    if(core->removeComponent("TestModule") == NULL)
        printf("FAILED To REMOVE TestModule!\n");
    printf("^^^ If nothing appears above, all tests passed!\n");
}
