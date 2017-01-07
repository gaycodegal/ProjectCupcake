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
    std::string compareto("{\"a\": -239402394,\"array\": [-1,-128,-256,-80000,1,2,127,255,30000,80000,],\"o\": nan,\"f\": 23423,\"j\": -inf}");
    
    if(m->compare(compareto) != 0){
        printf("failed pretty bson, returned: '''%s'''\n", m->c_str());
    }
    
    int formatLen = -1;
    char * formatted = formatBSON(val, formatLen);
    
    CharArray * formattedArray = new CharArray(formatted);
    delete m;
    m = asPretty(val);
    if(m->compare(compareto) != 0){
        printf("formatted, len: %i data: '''%s'''\n",formatLen,formatted);
        printf("failed conversion both ways bson io, returned: '''%s'''\n", m->c_str());
    }
    
    delete m;

    
    delete formattedArray;
    
    val->deleteData();
    delete array;
    delete val;
    return 0;
}
