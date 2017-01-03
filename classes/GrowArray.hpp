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
    /** the maximum size of the array before it must expand */
    unsigned int size_;
    /** the current amount of things in the array */
    unsigned int count_;
    /** stores the things */
    Data * array_;
    
    /** 
     expand the current max size
     */
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
    /**
     an array that grows by powers of two
     when it exceeds it capacity.
     
     mostly used for pushing things in
     and then accessing them by index.
     
     items will always be in the first
     count_ slots of the array_
     */
    GrowArray(int size = 32){
        count_ = 0;
        size_ = size;
        array_ = new Data[size_];
    }
    
    /**
     removes a section of the array and shifts
     everything else over to fill up the space
     */
    void remove(int from, int to){
        if(from > to)
            return;
        for(unsigned int i = to, j = from; i < count_; ++i, ++j){
            array_[j] = array_[i];
        }
        count_ -= to - from;
    }
    
    /**
     finds the index of something in the array
     return index or -1 if not found
     */
    int find(Data value) const{
        for(int i = 0; i < count_; ++i){
            if(array_[i] == value)
                return i;
        }
        return -1;
    }
    
    /**
     wipes the array clean
     */
    void wipe (){
        count_ = 0;
    }
    
    /**
     put something at the end of the array.
     */
    int push(Data data){
        if(count_ == size_)
            grow(size_ << 1);
        array_[count_] = data;
        return count_++;
    }
    
    /**
     get something at index i of the array.
     assumes it's a valid index
     */
    Data get(int i) const{
        return array_[i];
    }
    
    /**
     wipes the array clean
     and also deletes everything in the array
     */
    void drain(){
        for(unsigned int i = 0; i < count_; ++i){
            delete array_[i];
        }
        count_ = 0;
    }
    
    /**
     get the number of things in the array
     */
    int count() const{
        return count_;
    }
};

#endif /* GrowArray_hpp */
