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
        if(key != NULL){
            unsigned long length = std::strlen(key) + 1;
            this->key = new char[length];
            std::strcpy(this->key, key);
            this->key[length - 1] = '\0';
        }else{
            this->key = NULL;
        }
        this->hash = hash;
        this->value = value;
    }
    
    ~HashEntry(){
        if(key != NULL)
            delete [] key;
    }
    
    bool keyEquals(unsigned long hash, const char * other) {
        //Handles symbols
        if(key == NULL || other == NULL)
            return (hash == this->hash && key == NULL && other == NULL);
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
    
    Data getValue() const{
        return value;
    }
};

const int TABLE_SIZE = 32;

template <typename Obj>
class HashMap {
private:
    int size;
    int count_;
    int nrem;
    Obj nill;
    /** non conflicting nonsense key representing something was removed */
    HashEntry<Obj> * rem;
    HashEntry<Obj> **table;
    
    /**
     creates a new table and inserts everything held into that of
     a specified size.
     */
    void expand(int newsize){
        HashEntry<Obj> **oldTable = table;
        int oldSize = size;
        size = newsize;
        table = new HashEntry<Obj>*[size];
        for (int i = 0; i < size; i++)
            table[i] = NULL;
        
        nrem = count_ = 0;
        for (int i = 0; i < oldSize; i++){
            HashEntry<Obj> * entry = oldTable[i];
            if (entry != NULL && entry != rem){
                put(entry->key, entry->hash, entry->value);
                delete entry;
            }
        }
        delete[] oldTable;
    }
public:
    
    /**
     creates a hashmap with c_str keys
     */
    HashMap(int size = 32, Obj nill = 0) {
        this->nill = nill;
        this->rem = new HashEntry<Obj>("", stringHash("") + 1, nill); // will never match because hash is hash("") + 1
        this->size = size;
        nrem = count_ = 0;
        table = new HashEntry<Obj>*[size];
        for (int i = 0; i < size; i++)
            table[i] = NULL;
    }
    
    /**
     remove the thing at the key provided.
     */
    void remove(const char * key){
        delete this->removeEntry(key);
    }
    
    /**
     remove the thing at the symbol provided.
     */
    void remove(const unsigned long symbol){
        delete this->removeEntry(NULL, symbol);
    }
    
    /**
     remove the thing at the key provided.
     \return NULL if key is null, or the entry otherwise
     also NULL if not found
     */
    HashEntry<Obj> * removeEntry(const char * key){
        if(key == NULL)
            return NULL;
        unsigned long rhash = stringHash(key);
        return this->removeEntry(key, rhash);
    }
    
    /**
     remove the thing at the key provided.
     \return NULL if key is null, or the entry otherwise
     also NULL if not found
     */
    HashEntry<Obj> * removeEntry(const unsigned long symbol){
        return this->removeEntry(NULL, symbol);
    }
    
    /**
     remove the entry at key or symbol provided.
     note you'll need to delete the entry returned
     \return NULL if key is null, or the entry otherwise
     also NULL if not found

     */
    HashEntry<Obj> * removeEntry(const char * key, const unsigned long symbol){
        //technically not needed, but why not
        if(nrem + count_ >= (float)this->size * 0.7f){
            if(nrem > (float)this->size * 0.2f)
                this->expand(this->size);
            else
                this->expand(this->size << 1);
        }
       
        int hash = (symbol % size);
        
        while (table[hash] != NULL && (!table[hash]->keyEquals(symbol, key)))
            hash = (hash + 1) % size;
        
        if (table[hash] == NULL){
            return NULL;
        }else{
            HashEntry<Obj> * ret = table[hash];
            table[hash] = rem;
            ++nrem;
            --count_;
            return ret;
        }
    }
    
    /**
     get the first thing after an index in the table.
     useful for unstable iteration
     */
    Obj getAfter(int & i, char * &key){
        for(int j = i; j < size; ++j){
            HashEntry<Obj> * e = table[j];
            if(e != NULL && e != rem){
                i = j;
                key = e->key;
                return e->value;
            }
        }
        i = -1;
        key = NULL;
        return NULL;
    }
    
    /**
     returns the number of things in the 
     */
    int count(){
        return count_;
    }
    
    /**
     get the object stored at a key
     */
    Obj get(const char * key) const{
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
    
    /**
     get the object stored at a symbol
     */
    Obj get(const unsigned long symbol) const{
        int hash = (symbol % size);
        while (table[hash] != NULL && (!table[hash]->keyEquals(symbol, NULL)))
            hash = (hash + 1) % size;
        if (table[hash] == NULL)
            return nill;
        else
            return table[hash]->getValue();
    }
    
    /**
     put an object at a key.
     returns whether the object already existed
     */
    bool put(const char * key, Obj value) {
        
        return put(createEntry(key, value), key);
    }
    
    /**
     put an object at a symbol.
     returns whether the object already existed
     */
    bool put(const unsigned long symbol, Obj value) {
        return put(createEntry(NULL, symbol, value), NULL);
    }
    
    /**
     put an object at a key/symbol.
     returns whether the object already existed
     */
    bool put(const char * key, const unsigned long symbol, Obj value) {
        return put(createEntry(key, symbol, value), key);
    }
    
    /**
     create an entry for insertion into the table
     */
    HashEntry<Obj> *  createEntry(const char * key, Obj value) {
        if(nrem + count_ >= (float)this->size * 0.7f){
            if(nrem > (float)this->size * 0.2f)
                this->expand(this->size);
            else
                this->expand(this->size << 1);
        }
        unsigned long rhash = stringHash(key);
        return new HashEntry<Obj>(key, rhash, value);
    }
    
    /**
     create an entry for insertion into the table
     */
    HashEntry<Obj> *  createEntry(const char * key, const unsigned long symbol, Obj value) {
        if(nrem + count_ >= (float)this->size * 0.7f){
            if(nrem > (float)this->size * 0.2f)
                this->expand(this->size);
            else
                this->expand(this->size << 1);
        }
        return new HashEntry<Obj>(key, symbol, value);
    }
    
    /**
     puts an entry into the table at a key.
     */
    bool put(HashEntry<Obj> * entry, const char * key) {
        int was_extant = -1;
        
        
        HashEntry<Obj> * tomove = NULL;

        while(entry != NULL){

            long rhash = entry->hash;
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
            count_++;
            
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
    
    /**
     deletes everything in the table and wipes it
     */
    void drain(){
        nrem = count_ = 0;
        for (int i = 0; i < size; ++i){
            if (table[i] != NULL && table[i] != rem){
                delete table[i]->value;
                delete table[i];
                table[i] = NULL;
            }
        }
    }
    
    /**
     wipes the table
     */
    void wipe(){
        nrem = count_ = 0;
        for (int i = 0; i < size; ++i){
            if (table[i] != NULL && table[i] != rem)
                delete table[i];
            table[i] = NULL;
        }
    }
    
    /**
     deletes the table
     */
    ~HashMap() {
        for (int i = 0; i < size; ++i)
            if (table[i] != NULL && table[i] != rem)
                delete table[i];
        delete[] table;
        delete rem;
    }
};

#endif /* Hashmap_hpp */

