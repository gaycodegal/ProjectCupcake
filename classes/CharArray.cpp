//
//  CharArray.cpp
//  SLUG
//
//  Created by Steph on 6/28/16.
//
//

#include "CharArray.hpp"

CharArray::CharArray(char * buffer, int readHead){
    this->readHead = readHead;
    this->buffer = buffer;
    ownsBuffer = true;
}

CharArray::~CharArray(){
    if(ownsBuffer)
        delete [] buffer;
}

char * CharArray::getBuffer(){
    return buffer;
}

char * CharArray::getCString(int & len){
    bool knownlen = (len >= 0);
    int at = readHead;
    if(!knownlen){
        while (buffer[at] != '\0') {
            at++;
        }
        len = at;
    }else{
        at += len;
    }
    char * str = new char[at - readHead + 1];
    int i = 0;
    
    while(readHead < at){
        str[i++] = buffer[readHead++];
    }
    if(!knownlen)
        readHead++;
    str[i++] = 0;

    return str;
}

std::string * CharArray::getString(int & len){
    char * cstr = getCString(len);
    std::string * str = new std::string(cstr);
    delete cstr;
    return str;
}



void CharArray::rollBack(){
    readHead = 0;
}

void CharArray::rollBackBy(int amount){
    readHead -= amount;
    if(readHead < 0)
        readHead = 0;
}

Uint32 CharArray::getUint32(){
    Uint32 ret = ((buffer[readHead] & 0xFF) << 24) |
    ((buffer[readHead + 1] & 0xFF) << 16) |
    ((buffer[readHead + 2] & 0xFF) << 8) |
    (buffer[readHead + 3] & 0xFF);
    readHead += 4;
    return ret;
}

Uint16 CharArray::getUint16(){
    Uint16 ret = ((buffer[readHead] & 0xFF) << 8) |
    (buffer[readHead + 1] & 0xFF);
    readHead += 2;
    return ret;
}

Uint8 CharArray::getUint8(){
    return (buffer[readHead++] & 0xFF);
}

float CharArray::getFloat(){
    uint32_t ui = ((buffer[readHead] & 0xFF) << 24) |
    ((buffer[readHead + 1] & 0xFF) << 16) |
    ((buffer[readHead + 2] & 0xFF) << 8) |
    (buffer[readHead + 3] & 0xFF);
    readHead += 4;
    float f;
    memcpy(&f, &ui, 4);
    return f;
}

int32_t CharArray::getInt32(){
    int32_t ret = ((buffer[readHead] & 0xFF) << 24) |
    ((buffer[readHead + 1] & 0xFF) << 16) |
    ((buffer[readHead + 2] & 0xFF) << 8) |
    (buffer[readHead + 3] & 0xFF);
    readHead += 4;
    return ret;
}

int16_t CharArray::getInt16(){
    int16_t ret = ((buffer[readHead] & 0xFF) << 8) |
    (buffer[readHead + 1] & 0xFF);
    readHead += 2;
    return ret;
}

int8_t CharArray::getInt8(){
    return (buffer[readHead++] & 0xFF);
}


