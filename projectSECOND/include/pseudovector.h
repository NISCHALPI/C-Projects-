#ifndef __PSEUDOVECTOR__
#define __PSEUDOVECTOR__

//Includes Custom Libraries
#include "../../lib/sort/nlogn/mergesort.h"
#include "../../lib/sort/nlogn/quicksort.h"
#include "../../lib/search/binary.h" 


template <typename Item>
class PseudoVector{

    private:
            Item* __array ;
            unsigned int __block;
            unsigned int __size ;
            bool __isSorted;
    public:
   
    PseudoVector();
    ~PseudoVector();

    Item at(unsigned int index) const;

    //sort ing 
    void sort(bool typesort);

    //void push_back(Item& itemRef);
    void push_back(Item itemRef);
    
    // get size of vector 
    int getSize() const{
        return __size;
    }

    //__block size
    int viewBlock() const{
        return __block;

    }

    int find(Item toFind);

    //Pseudovector
    void unique(PseudoVector& temp);

};

template <typename Item>
PseudoVector<Item>::PseudoVector(){
    __block = 100;

    __array = (Item*)malloc( __block * sizeof(Item));
    __size = 0;
    __isSorted = false;
    


}

// Destructor
template <typename Item>
PseudoVector<Item>::~PseudoVector(){

free(__array);

}


// at 
template <typename Item>
Item PseudoVector<Item>::at( unsigned int index) const{

if ( index > __size -1 || index < 0){
    std::cout << "Out of Index!" << std::endl;
    exit(-1);
}
else{

    return *(__array + index);
}
}



// MergeSort = true || QuickSort == false
template <typename Item>
void PseudoVector<Item>::sort(bool typesort){

if (typesort){
mergesort::mergeSort(__array, 0, __size -1);
}
else{
    quicksort::quickSort(__array , 0 , __size -1);
}
__isSorted = true;
return ;
}



// Pushback implementation
template <typename Item>
void PseudoVector<Item>::push_back(Item itemRef){

if (__size == 0){
    __array[0] = itemRef;
    __size++;
}
else{
    __size++;

    if ( __size > __block){
        
        //Logarithmic memory allocation model assencion model 
        __block = int(log10(__block)) * __block ;
        
        __array = (Item*)realloc(this->__array , __block *sizeof(Item));

        __array[__size - 1] = itemRef;
        
    }
    else {
        __array[__size -1 ] = itemRef;
    }
    

}
}


// Returns a pseudovector of unique items 
template <typename Item>
int PseudoVector<Item>::find(Item toFind){

return binary_search::binarySearch(__array , toFind , 0 , __size -1);
}

// Returns a pseudovector of unique items 
template <typename Item>
void PseudoVector<Item>::unique(PseudoVector<Item>& temp){

    // Add first 
    temp.push_back(__array[0]);
    
    for (int i =1; i< __size ; i++){
        if (temp.find(__array[i]) == -1){
            temp.push_back(__array[i]);
        }
    }

    
}









#endif