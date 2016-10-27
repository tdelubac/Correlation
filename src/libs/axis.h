#ifndef DEF_AXIS
#define DEF_AXIS

#include <iostream>
#include <vector>

template<class TYPE>
class Axis: public std::vector<TYPE>
{
 public:
    const int getBin(TYPE val)
    /// Return the value of the bin in which val belongs.
    /// Return 0 in case axis size is 1 (Trick to make 1D profile works).
    /// Return -1 in case this bin is not defined (axis has less than 1 bin or val is out of the axis range). 
    {
        if(this->size() == 0){
            throw std::range_error("Axis::getBin(TYPE val): axis has size 0. Behaviour of getBin method undefined.");
            return -1;
        }
        if(this->size() == 1){
            return 0;
        }
        if(val < this->front()){
            throw std::out_of_range("Axis::getBin(TYPE val): val is inferior to axis lower bound.");
            return -1;
        }
        if (val >= this->back()){
            throw std::out_of_range("Axis::getBin(TYPE val): val is superior to axis higher bound.");
            return -1;
        }
        size_t first = 0;
        size_t last = this->size()-1;
        while (first <= last){
            size_t mid = (first+last)/2;
            if (val >= this->data()[mid+1])
                first = mid+1;
            else if (val< this->data()[mid])
                last = mid;
            else
                return mid;
        }
        return -1;
    }
}; 

#endif
