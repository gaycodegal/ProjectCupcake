//
//  test_queue.cpp
//  Cupcake-Mac
//
//  Created by Steph on 1/1/17.
//
//


#include <stdio.h>
#include "test_iter_hash.hpp"
#include "testing_functions.hpp"

int test_iter_hash(){
    
    IterableHashMap<int> * temp = new IterableHashMap<int>(8,-1);
    temp->put("TestModule", 111);
    temp->put("A", 1);
    temp->put("c", 2);
    temp->put("T", 3);
    temp->put("g", 4);
    
    assertEq(temp->get("TestModule"), 111, "fail get / put");
    assertEq(temp->get("g"), 4, "fail get / put");
    assertEq(temp->get("A"), 1, "fail get / put");
    assertEq(temp->get("b"), -1, "fail get / put");
    assertEq(temp->get("T"), 3, "fail get / put");
    assertEq(temp->get("c"), 2, "fail get / put");
    
    temp->remove("TestModule");
    assertEq(temp->get("TestModule"), -1, "fail get / put");

    
    temp->put("v", 9);
    temp->put("d", 10);
    temp->put("a", 11);
    temp->put("f", 12);
    
    assertEq(temp->get("v"), 9, "fail get / put");
    assertEq(temp->get("d"), 10, "fail get / put");
    assertEq(temp->get("a"), 11, "fail get / put");
    assertEq(temp->get("f"), 12, "fail get / put");
    
    assertEq(temp->get("g"), 4, "fail get / put");
    assertEq(temp->get("A"), 1, "fail get / put");
    assertEq(temp->get("b"), -1, "fail get / put");
    assertEq(temp->get("T"), 3, "fail get / put");
    assertEq(temp->get("c"), 2, "fail get / put");
    
    temp->put("v", 7);
    temp->put("d", 6);
    
    
    temp->put("b", 8);
    
    assertEq(temp->get("v"), 7, "fail expand / replace");
    assertEq(temp->get("d"), 6, "fail expand");
    assertEq(temp->get("a"), 11, "fail expand");
    assertEq(temp->get("f"), 12, "fail expand");
    
    assertEq(temp->get("g"), 4, "fail expand");
    assertEq(temp->get("A"), 1, "fail expand");
    assertEq(temp->get("b"), 8, "fail expand");
    assertEq(temp->get("T"), 3, "fail expand");
    assertEq(temp->get("c"), 2, "fail expand");
    
    temp->remove("a");
    temp->remove("T");
    temp->remove("v");
    
    assertEq(temp->get("a"), -1, "fail rem");
    assertEq(temp->get("T"), -1, "fail rem");
    assertEq(temp->get("v"), -1, "fail rem");
    
    assertEq(temp->get(0), 1, "fail iteration 0");
    assertEq(temp->get(1), 2, "fail iteration 1");
    assertEq(temp->get(2), 4, "fail iteration 2");
    assertEq(temp->get(3), 12, "fail iteration 3");
    assertEq(temp->get(4), 6, "fail iteration 4");
    assertEq(temp->get(5), 8, "fail iteration 5");
    
    
    return 0;
}


