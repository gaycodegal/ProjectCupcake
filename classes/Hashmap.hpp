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
    char * key;
    unsigned long hash;
    Data value;
    HashEntry(const char * key, unsigned long hash, Data value) {
        unsigned long length = std::strlen(key) + 1;
        this->key = new char[length];
        std::strcpy(this->key, key);
        this->key[length - 1] = '\0';
        this->hash = hash;
        this->value = value;
    }
    
    ~HashEntry(){
        delete [] this->key;
    }
    
    bool keyEquals(unsigned long hash, const char * other) {
        if(hash != this->hash){
            return false;
        }
        bool compare = true;
        int c = 0;
        while(compare){
            if(key[c] != other[c]){
                return false;
            }
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
    int nrem;
    Obj nill;
    HashEntry<Obj> * rem;
    HashEntry<Obj> **table;
    
    void expand(int newsize){
        HashEntry<Obj> **oldTable = table;
        int oldSize = size;
        size = newsize;
        table = new HashEntry<Obj>*[size];
        for (int i = 0; i < size; i++)
            table[i] = NULL;
        
        nrem = count = 0;
        for (int i = 0; i < oldSize; i++){
            if (oldTable[i] != NULL && oldTable[i] != rem){
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
        this->rem = new HashEntry<Obj>("", stringHash("") + 1, nill); // will never match because hash is hash("") + 1
        this->size = size;
        nrem = count = 0;
        table = new HashEntry<Obj>*[size];
        for (int i = 0; i < size; i++)
            table[i] = NULL;
    }
    
    HashEntry<Obj> * remove(const char * key){
        //technically not needed, but why not
        if(nrem + count >= (float)this->size * 0.7f){
            if(nrem > (float)this->size * 0.2f)
                this->expand(this->size);
            else
                this->expand(this->size << 1);
        }
        
        if(key == NULL)
            return NULL;
        
        unsigned long rhash = stringHash(key);
        int hash = (rhash % size);
        
        while (table[hash] != NULL && (!table[hash]->keyEquals(rhash, key)))
            hash = (hash + 1) % size;
        
        if (table[hash] == NULL){
            return NULL;
        }else{
            HashEntry<Obj> * ret = table[hash];
            table[hash] = rem;
            ++nrem;
            --count;
            return ret;
        }
    }
    
    Obj get(const char * key) {
        if(key == NULL)
            return nill;
        unsigned long rhash = stringHash(key);
        int hash = (rhash % size);
        while (table[hash] != NULL && (!table[hash]->keyEquals(rhash, key)))
            hash = (hash + 1) % size;
        if (table[hash] == NULL)
            return nill;
        else
            return table[hash]->getValue();
    }
    
    bool put(const char * key, Obj value) {
        return put(createEntry(key, value), key);
    }
    
    HashEntry<Obj> *  createEntry(const char * key, Obj value) {
        if(nrem + count >= (float)this->size * 0.7f){
            if(nrem > (float)this->size * 0.2f)
                this->expand(this->size);
            else
                this->expand(this->size << 1);
        }
        unsigned long rhash = stringHash(key);
        return new HashEntry<Obj>(key, rhash, value);
    }
    
    bool put(HashEntry<Obj> * entry, const char * key) {
        int was_extant = -1;
        
        
        HashEntry<Obj> * tomove = NULL;

        while(entry != NULL){

            int rhash = entry->hash;
            int hash = (rhash % size);
        
            // rekey entry in major position if it's not already in major position
            if(table[hash] != NULL && table[hash] != rem && table[hash]->hash % size != hash){
                tomove = table[hash];
                table[hash] = NULL;
            }
            
            //find location to put. will pick major if available
            while (table[hash] != NULL && table[hash] != rem && !(table[hash]->keyEquals(rhash, key))){
                hash = (hash + 1) % size;
            }
            
            //delete if we're already extant, dec nrem if nesc.
            if(table[hash] == rem){
                --nrem;
            }else if (table[hash] != NULL){
                if(was_extant == -1)
                    was_extant = 1;
                delete table[hash];
            }
            if(was_extant == -1)
                was_extant = 0;
            table[hash] = entry;
            count++;
            
            //doesn't require size checking, as there will be room
            if(tomove != NULL){
                entry = tomove;
                key = entry->key;
                tomove = NULL;
            }else{
                entry = NULL;
            }
        }
        return was_extant == 1;
    }
    
    void drain(){
        nrem = count = 0;
        for (int i = 0; i < size; ++i){
            if (table[i] != NULL && table[i] != rem){
                delete table[i]->value;
                delete table[i];
                table[i] = NULL;
            }
        }
    }
    
    void wipe(){
        for (int i = 0; i < size; ++i){
            if (table[i] != NULL && table[i] != rem)
                delete table[i];
            table[i] = NULL;
        }
    }
    
    ~HashMap() {
        for (int i = 0; i < size; ++i)
            if (table[i] != NULL && table[i] != rem)
                delete table[i];
        delete[] table;
        delete rem;
    }
};

#endif /* Hashmap_hpp */

