//
//  GrowArray.hpp
//  SLUG
//
//  Created by Steph on 12/15/16.
//
//

#ifndef GrowArray_hpp
#define GrowArray_hpp

#include <stdio.h>

template <typename Data>
class GrowArray{
    unsigned int size_;
    unsigned int count_;
    Data * array_;
    
    void grow(int size){
        Data * old_array = array_;
        size_ = size;
        array_ = new Data[size_];
        for(unsigned int i = 0; i < count_; ++i){
            array_[i] = old_array[i];
        }
        delete [] old_array;
    }
    
public:
    GrowArray(int size = 32){
        count_ = 0;
        size_ = size;
        array_ = new Data[size_];
    }
    
    int push(Data data){
        if(count_ == size_)
            grow(size_ << 1);
        array_[count_] = data;
        return count_++;
    }
    
    Data get(int i){
        return array_[i];
    }
    
    void drain(){
        for(unsigned int i = 0; i < count_; ++i){
            delete array_[i];
        }
        count_ = 0;
    }
    
    int count(){
        return count_;
    }
};

#endif /* GrowArray_hpp */
