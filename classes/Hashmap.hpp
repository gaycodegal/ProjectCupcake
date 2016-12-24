//
//  Hashmap.hpp
//  SLUG
//
//  Created by Steph on 7/12/16.
//
//

#ifndef Hashmap_hpp
#define Hashmap_hpp

#include <stdio.h>
#include <string>

unsigned long stringHash(const char * str);

template <typename Data>
class HashEntry {
public:
    const char * key;
    Data value;
    HashEntry(const char * key, Data value) {
        this->key = key;
        this->value = value;
    }
    bool keyEquals(const char * other) {
        bool compare = true;
        int c = 0;
        while(compare){
            if(key[c] != other[c])
                return false;
            compare = key[c] == '\0';
        }
        return true;
    }
    
    Data getValue() {
        return value;
    }
};

const int TABLE_SIZE = 32;

template <typename Obj>
class HashMap {
private:
    int size;
    int count;
    Obj nill;
    HashEntry<Obj> **table;
    
    void expand(){
        HashEntry<Obj> **oldTable = table;
        int oldSize = size;
        size <<= 1;
        table = new HashEntry<Obj>*[size];
        for (int i = 0; i < size; i++)
            table[i] = NULL;
        
        for (int i = 0; i < oldSize; i++){
            if (oldTable[i] != NULL){
                put(oldTable[i]->key, oldTable[i]->value);
                delete oldTable[i];
            }
        }
        delete[] oldTable;
        
    }
public:
    //
    HashMap(int size = 32, Obj nill = 0) {
        this->nill = nill;
        this->size = size;
        count = 0;
        table = new HashEntry<Obj>*[size];
        for (int i = 0; i < size; i++)
            table[i] = NULL;
    }
    
    Obj get(const char * key) {
        if(key == NULL)
            return NULL;
        int hash = (stringHash(key) % size);
        while (table[hash] != NULL && (!table[hash]->keyEquals(key)))
            hash = (hash + 1) % size;
        if (table[hash] == NULL)
            return nill;
        else
            return table[hash]->getValue();
    }
    
    void put(const char * key, Obj value) {
        int hash = (stringHash(key) % size);
        while (table[hash] != NULL && !(table[hash]->keyEquals(key)))
            hash = (hash + 1) % size;
        if (table[hash] != NULL)
            delete table[hash];
        table[hash] = new HashEntry<Obj>(key, value);
        count++;
    }
    
    void drain(){
        for (int i = 0; i < size; i++){
            if (table[i] != NULL){
                delete table[i]->value;
                delete table[i];
                table[i] = NULL;
            }
        }
    }
    
    ~HashMap() {
        for (int i = 0; i < size; i++)
            if (table[i] != NULL)
                delete table[i];
        delete[] table;
    }
};

#endif /* Hashmap_hpp */

