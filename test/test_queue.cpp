//
//  test_queue.cpp
//  Cupcake-Mac
//
//  Created by Steph on 1/1/17.
//
//


#ifndef cpp_test_queue
#define cpp_test_queue
#include <stdio.h>
#include "Queue.hpp"

int test_queue(){
    Queue<int> * temp = new Queue<int>(8,-1);
    for(int i = 0; i < 4; ++i){
        temp->push(i);
    }
    
    for(int i = 0; i < 4; ++i){
        if(temp->poll() != i){
            printf("Queue failing: push or poll\n");
        }
    }
    
    for(int i = 0; i < 12; ++i){
        temp->push(i);
    }
    
    for(int i = 0; i < 12; ++i){
        int r = temp->poll();
        if(r != i){
            printf("Queue failing: expand or poll\n");
            printf("expected: %i got %i\n", i, r);
        }
    }
    
    for(int i = 0; i < 12; ++i)
        temp->push(i);
    
    for(int i = 0; i < 4; ++i){
        temp->remove(i * 3);
    }
    
    for(int i = 0; i < 8; ++i){
        int r = temp->poll();
        if(r % 3 == 0){
            printf("Queue failing: remove or poll\n");
            printf("expected to not get: %i got %i\n", i, r);
        }
    }
    
    delete temp;

    return 0;
}

#endif /* cpp_test_queue */

