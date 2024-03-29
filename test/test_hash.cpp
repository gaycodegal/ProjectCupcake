//
//  test_queue.cpp
//  Cupcake-Mac
//
//  Created by Steph on 1/1/17.
//
//


#include <stdio.h>
#include "test_hash.hpp"
#include "testing_functions.hpp"

int test_hash(){
    
    HashMap<int> * temp = new HashMap<int>(8,-1);
    temp->put("A", 1);
    temp->put("c", 2);
    temp->put("T", 3);
    temp->put("g", 4);
    
    assertEq(temp->get("g"), 4, "fail get / put");
    assertEq(temp->get("A"), 1, "fail get / put");
    assertEq(temp->get("b"), -1, "fail get / put");
    assertEq(temp->get("T"), 3, "fail get / put");
    assertEq(temp->get("c"), 2, "fail get / put");
    
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
    
    
    temp->put("b", 8);
    
    assertEq(temp->get("v"), 7, "fail expand / replace");
    assertEq(temp->get("d"), 10, "fail expand");
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
    
    temp->put(1235, 6);
    temp->put(3128, 7);
    temp->put(1349, 8); // if an error occurrs here it's due to re-keying
    
    assertEq(temp->get("v"), -1, "fail symbol insertion");
    assertEq(temp->get("d"), 10, "fail symbol insertion");
    assertEq(temp->get("a"), -1, "fail symbol insertion");
    assertEq(temp->get("f"), 12, "fail symbol insertion");
    
    
    assertEq(temp->get(1235), 6, "fail symbol insertion");
    
    assertEq(temp->get("g"), 4, "fail symbol insertion");
    assertEq(temp->get("A"), 1, "fail symbol insertion");
    assertEq(temp->get("b"), 8, "fail symbol insertion");
    
    assertEq(temp->get(3128), 7, "fail symbol insertion");
    assertEq(temp->get(1349), 8, "fail symbol insertion");
    
    assertEq(temp->get("T"), -1, "fail symbol insertion");
    assertEq(temp->get("c"), 2, "fail symbol insertion");
    
    temp->remove(3128);
    
    
    assertEq(temp->get("v"), -1, "fail symbol removal");
    assertEq(temp->get("d"), 10, "fail symbol removal");
    assertEq(temp->get("a"), -1, "fail symbol removal");
    assertEq(temp->get("f"), 12, "fail symbol removal");
    
    
    assertEq(temp->get(1235), 6, "fail symbol removal");
    
    assertEq(temp->get("g"), 4, "fail symbol removal");
    assertEq(temp->get("A"), 1, "fail symbol removal");
    assertEq(temp->get("b"), 8, "fail symbol removal");
    
    assertEq(temp->get(3128), -1, "fail symbol removal");
    assertEq(temp->get(1349), 8, "fail symbol removal");
    
    assertEq(temp->get("T"), -1, "fail symbol removal");
    assertEq(temp->get("c"), 2, "fail symbol removal");

    delete temp;

    return 0;
}


