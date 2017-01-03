//
//  testing_functions.hpp
//  Cupcake-Mac
//
//  Created by Steph on 1/2/17.
//
//

#ifndef testing_functions_hpp
#define testing_functions_hpp

#include <stdio.h>

/**
 assert that two things are equal =
 if they are != present message
 */
template <typename Data>
void assertEq(Data a, Data b, const char * mess = ""){
    if (a != b)
        printf("%s\n", mess);
}

#endif /* testing_functions_hpp */
