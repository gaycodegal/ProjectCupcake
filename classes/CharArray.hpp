//
//  CharArray.hpp
//  SLUG
//
//  Created by Steph on 6/28/16.
//
//

#ifndef CharArray_hpp
#define CharArray_hpp
#define getNthBool(b,n) (b&(1<<(7-n)))

#include <stdio.h>
#include "SDL.h"
#include <string>

class CharArray {
private:
    int readHead;
    char * buffer;
    bool ownsBuffer;
public:
    CharArray(char * buffer, int readHead = 0);
    ~CharArray();
    char * getCString(int & len);
    char * getBuffer();
    std::string * getString(int & len);
    void rollBack();
    void rollBackBy(int amount);
    Uint32 getUint32();
    Uint16 getUint16();
    Uint8 getUint8();
    
    int32_t getInt32();
    int16_t getInt16();
    int8_t getInt8();
    
    float getFloat();
    
};


#endif /* CharArray_hpp */
