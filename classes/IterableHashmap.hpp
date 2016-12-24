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
    HashMap<int> * map_;
    GrowArray<Data> * array_;
    Data nill_;
public:
    
    IterableHashMap(Data nill = 0) {
        nill_ = nill;
        map_ = new HashMap<int>(32, -1);
        array_ = new GrowArray<Data>(32);
    }
    
    int count(){
        return array_->count();
    }
    
    Data get(int i){
        return array_->get(i);
    }
    
    Data get(const char * key) {
        int location = map_->get(key);
        if(location == -1)
            return nill_;
        return array_->get(location);
    }
    
    void put(const char * key, Data value) {
        int location = array_->push(value);
        map_->put(key, location);
    }
    
    void drain(){
        
    }
    
    ~IterableHashMap() {
        
    }
};

#endif /* IterableHashmap_hpp */

