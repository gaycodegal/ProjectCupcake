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
    /**
     a hash map, but you can iterate it's contents
     only use if you need the ability to iterate contents
     */
    IterableHashMap(int size = 32, Data nill = 0) {
        nill_ = nill;
        map_ = new HashMap<Data>(32, nill);
        array_ = new GrowArray<HashEntry<Data> *>(32);
    }
    
    /**
     returns the number of things held
     */
    int count() const{
        return array_->count();
    }
    
    /**
     returns the thing at key i. does not
     check if i is valid
     */
    Data get(const int i) const{
        return array_->get(i)->value;
    }
    
    /**
     remove a thing at key
     expensive
     */
    Data remove(const char * key){
        HashEntry<Data> * entry = map_->removeEntry(key);
        if(entry == NULL) return nill_;
        int where = array_->find(entry);
        if(where == -1) return nill_;
        array_->remove(where, where + 1);
        Data value = entry->value;
        delete entry;
        return value;
    }
    
    /**
    get the thing at key
    */
    Data get(const char * key) const{
        return map_->get(key);
    }
    
    /**
     put something at a key
     expensive to replace
     */
    void put(const char * key, Data value) {
        HashEntry<Data> * entry = map_->removeEntry(key);
        if(entry != NULL){
            int where = array_->find(entry);
            if(where != -1){
                array_->remove(where, where + 1);
            }
            delete entry;
        }
        entry = map_->createEntry(key, value);
        map_->put(entry, key);
        array_->push(entry);
    }
    
    /**
     delete everything in the table, wipe
     */
    void drain(){
        array_->drain();
        map_->wipe();
    }
    
    /**
     deletes the table and array
     */
    ~IterableHashMap() {
        delete map_;
        delete array_;
    }
};

#endif /* IterableHashmap_hpp */

