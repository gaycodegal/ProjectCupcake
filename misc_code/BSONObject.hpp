//
//  BSONObject.hpp
//  Cupcake-Mac
//
//  Created by Steph on 1/3/17.
//
//

#ifndef BSONObject_hpp
#define BSONObject_hpp

#include <stdio.h>
#include <string>
#include <sstream>
#include "Hashmap.hpp"
#include "GrowArray.hpp"
#include "CharArray.hpp"

class BSONObject;
class BSONArray;

class BSONvalue;

union BSONdata{
    float _float;
    int _int;
    unsigned int _uint;
    std::string * _string;
    HashMap<BSONvalue *> * _object;
    GrowArray<BSONvalue *> * _array;
};

class BSONvalue{
public:
    int type;
    BSONdata data;
    BSONvalue();
    BSONvalue(int type, BSONdata data);
    void changeTo(int type, BSONdata data, bool doDelete);
    void deleteData();
    ~BSONvalue();
};

std::string * asPretty(BSONvalue * val);

void asPretty(BSONvalue * val, std::stringstream & stream);

BSONvalue * parseBSON(CharArray * array);

#endif /* BSONObject_hpp */
