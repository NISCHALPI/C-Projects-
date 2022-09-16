#ifndef __PSEUDOVECTOR__
#define __PSEUDOVECTOR__

//Includes Custom Libraries
#include "../../lib/sort/nlogn/mergesort.h"
#include "../../lib/sort/nlogn/quicksort.h"
#include "../../lib/search/binary.h" 


template <typename Item>
class PseudoVector{

    private:
            Item* __array = nullptr;
            unsigned int __size = 0;
            bool __isSorted = false;
    public:

    PseudoVector();
    
    ~PseudoVector();

    Item at(unsigned int index) const;

    //sort ing 
    void sort(bool typesort);

    //void push_back(Item& itemRef);
    void push_back(Item itemRef);
    
    // get size of vector 
    int getSize(){
        return __size;
    }

    //get unique 
    void  unique(PseudoVector<Item>& test);

    int find(Item toFind);

};

//Constructer 
template <typename Item>
PseudoVector<Item>::PseudoVector(){

__array = (Item*)malloc(sizeof(Item));

__size = 0;

}

// Destructor
template <typename Item>
PseudoVector<Item>::~PseudoVector(){
free(__array);
}


// at 
template <typename Item>
Item PseudoVector<Item>::at( unsigned int index) const{

if ( index >= __size || index < 0){
    throw  "std::out_of_range error";
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

if(__size == 0){
    
    *__array = itemRef;
    
    __size++;
}
else{
   __array = (Item*)realloc(__array , (__size + 1) *sizeof(Item));
   __array[__size] = itemRef;
   __size++;  
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