//
//  Hashmap.hpp
//  SLUG
//
//  Created by Steph on 7/12/16.
//
//

#ifndef IterableHashmap_hpp
#define IterableHashmap_hpp

#include <stdio.h>
#include "Hashmap.hpp"
#include "GrowArray.hpp"

template <typename Data>
class IterableHashMap {
private:
    HashMap<Data> * map_;
    GrowArray<HashEntry<Data> *> * array_;
    Data nill_;
public:
    
    IterableHashMap(int size = 32, Data nill = 0) {
        nill_ = nill;
        map_ = new HashMap<Data>(32, nill);
        array_ = new GrowArray<HashEntry<Data> *>(32);
    }
    
    int count(){
        return array_->count();
    }
    
    Data get(int i){
        return array_->get(i)->value;
    }
    
    Data remove(const char * key){
        HashEntry<Data> * entry = map_->remove(key);
        if(entry == NULL) return nill_;
        int where = array_->find(entry);
        if(where == -1) return nill_;
        array_->remove(where, where + 1);
        return entry->value;
    }
    
    Data get(const char * key) {
        return map_->get(key);
    }
    
    void put(const char * key, Data value) {
        HashEntry<Data> * entry = map_->remove(key);
        if(entry != NULL){
            int where = array_->find(entry);
            if(where != -1){
                array_->remove(where, where + 1);
            }
        }
        entry = map_->createEntry(key, value);
        map_->put(entry, key);
        array_->push(entry);
    }
    
    void drain(){
        array_->drain();
        map_->wipe();
    }
    
    ~IterableHashMap() {
        delete map_;
        delete array_;
    }
};

#endif /* IterableHashmap_hpp */

