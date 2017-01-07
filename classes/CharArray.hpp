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
    CharArray(char * buffer, const int readHead = 0, const bool owner = true);
    ~CharArray();
    char * getCString(int & len);
    char * getBuffer();
    std::string * getString(int & len);
    void rollBack();
    void rollBackBy(int amount);
    
    Uint32 getUint32();
    Uint16 getUint16();
    Uint8 getUint8();
    
    void writeUint32(uint32_t n);
    void writeUint16(uint16_t n);
    void writeUint8(uint8_t n);
    
    int32_t getInt32();
    int16_t getInt16();
    int8_t getInt8();
    
    void writeInt32(int32_t n);
    void writeInt16(int16_t n);
    void writeInt8(int8_t n);
    
    float getFloat();
    
    void writeFloat(float f);
    
    void writeString(const std::string * s, const bool nullTerm = false);
};


#endif /* CharArray_hpp */
