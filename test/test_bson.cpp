//
//  test_bson.cpp
//  Cupcake-Mac
//
//  Created by Steph on 1/4/17.
//
//

#include "test_bson.hpp"

int test_bson(){
    char * file = file_read("resources/test.bson");
    if(file == NULL)
        return 1;
    CharArray * array = new CharArray(file);
    BSONvalue * val = parseBSON(array);
    std::string * m = asPretty(val);
    if(m->compare("{\"f\": 23423,\n\"o\": nan,\n\"a\": -239402394,\n\"j\": -inf,\n}") != 0){
        printf("failed pretty bson, returned: %s", m->c_str());
    }
    val->deleteData();
    delete m;
    delete array;
    delete val;
    return 0;
}
