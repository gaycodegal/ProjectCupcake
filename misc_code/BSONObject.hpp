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
    BSONvalue(int32_t number);
    BSONvalue(uint32_t number);
    /**
     WARNING we will delete string if doDelete is called on us.
     */
    BSONvalue(std::string * string);
    /**
     WARNING we will delete object if doDelete is called on us.
     */
    BSONvalue(HashMap<BSONvalue *> * object);
    /**
     WARNING we will delete array if doDelete is called on us.
     */
    BSONvalue(GrowArray<BSONvalue *> * array);
    BSONvalue(int type, BSONdata data);
    
    void changeTo(int type, BSONdata data, bool doDelete);
    void deleteData();
    ~BSONvalue();
};

char * formatBSON(const BSONvalue * value, int & length);

std::string * asPretty(const BSONvalue * val);

void asPretty(const BSONvalue * val, std::stringstream & stream);

BSONvalue * parseBSON(CharArray * array);

#endif /* BSONObject_hpp */
