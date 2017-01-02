//
//  Queue.hpp
//  SLUG
//
//  Created by Steph on 12/15/16.
//
//

#ifndef Queue_hpp
#define Queue_hpp

#include <stdio.h>

template <typename Data>
class Queue{
    unsigned int size_;
    unsigned int start_;
    unsigned int end_;
    Data nill_;
    unsigned int count_;
    unsigned int rem_;
    Data * array_;
    
    void grow(int size){
        Data * old_array = array_;
        
        unsigned int oldsize = size_;
        
        size_ = size;
        array_ = new Data[size_];
        int i = start_, j = 0;
        do{
            if(array_[i] != nill_){
                array_[j++] = old_array[i];
            }
            
            ++i;
            if(i == oldsize)
                i = 0;
        }while(i != end_);
        
        start_ = rem_ = 0;
        end_ = count_;
        delete [] old_array;
    }
    
public:
    Queue(int size = 32, Data nill = 0){
        nill_ = nill;
        count_ = 0;
        rem_ = 0;
        start_ = end_ = 0;
        size_ = size;
        
        array_ = new Data[size_];
    }
    
    void push(Data data){
        if(rem_ + count_ == size_){
            if (rem_ >= (count_ >> 1))
                grow(size_);
            else
                grow(size_ << 1);
        }
        array_[end_] = data;
        ++count_;
        ++end_;
        // more efficient than mod.
        if(end_ == size_)
            end_ = 0;
    }
    
    void remove(Data data){
        int i = start_;
        do{
            if(array_[i] == data){
                array_[i] = nill_;
                break;
            }
            
            //more efficient than mod
            ++i;
            if(i == size_)
                i = 0;
        }while(i != end_);
        ++rem_;
    }
    
    Data poll(){
        if(count_ == 0)
            return nill_;
        --count_;
        unsigned int i = start_;
        while (array_[i] == nill_) {
            ++i;
            if(i == size_)
                i = 0;
        }
        Data ret = array_[i];
        start_ = i + 1;
        if(start_ == size_)
            start_ = 0;
        return ret;
    }
    
    Data peek() const{
        if(count_ == 0)
            return nill_;
        unsigned int i = start_;
        while (array_[i] == nill_) {
            ++i;
            if(i == size_)
                i = 0;
        }
        start_ = i;
        return array_[i];
    }
    
    Data get(const int i) const{
        return array_[i];
    }
    
    /**
     calls delete on every element inside the queue, resets
     to empty
     */
    void drain(){
        if(start_ < end_){
            for(unsigned int i = start_; i < end_; ++i){
                if(array_[i] != nill_)
                    delete array_[i];
            }
        }else{ // faster than using mod
            for(unsigned int i = start_; i < size_; ++i){
                if(array_[i] != nill_)
                    delete array_[i];
            }
            for(unsigned int i = 0; i < end_; ++i){
                if(array_[i] != nill_)
                    delete array_[i];
            }
        }
        start_ = end_ = count_ = 0;
    }
    
    /**
     
     */
    int count() const{
        return count_;
    }
};

#endif /* Queue_hpp */
