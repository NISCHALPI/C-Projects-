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
            size_t  __block;
            size_t  __size ;
            bool __isSorted;
    public:
    
    // Rule of 3 Inmplementation 
    PseudoVector();
    ~PseudoVector();
    PseudoVector(const PseudoVector<Item>& toCopy);
    PseudoVector<Item>& operator=( const PseudoVector<Item>& toCopy);



    // At Implementation
    Item at( int index) const;

    //sorting 
    void sort(bool typesort = true);

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

    // Find Function 
    int find(Item toFind);

    //Pseudovector
    void unique(PseudoVector& temp);

};



// Copy Constructer 
template <typename Item>
PseudoVector<Item>::PseudoVector(const PseudoVector<Item>& objtoCopy){

// Copy Defaults 
this->__block = objtoCopy.__block;
this->__isSorted = objtoCopy.__isSorted;
this->__size = objtoCopy.__size;

// New Malloc

this->__array = new Item[__block];


// Copy data 
for(int i=0; i< __size; i++){
    this->__array[i] = objtoCopy.__array[i];
}

}


// Equality operator 
template <typename Item>
PseudoVector<Item>& PseudoVector<Item>::operator=(const PseudoVector<Item>& objtoCopy){

// Copy Defaults 
this->__block = objtoCopy.__block;
this->__isSorted = objtoCopy.__isSorted;
this->__size = objtoCopy.__size;

// First Free the Block
delete[] __array;

// Then Reallocate 
this->__array = new Item[__block];


// Copy data 
for(int i=0; i< __size; i++){
    this->__array[i] = objtoCopy.__array[i];
}

return *this ;
}




template <typename Item>
PseudoVector<Item>::PseudoVector(){
    __block = 100;

    __array = new Item[__block];


    __size = 0;
    __isSorted = false;
    


}

// Destructor
template <typename Item>
PseudoVector<Item>::~PseudoVector(){


delete[] __array;


}


// at 
template <typename Item>
Item PseudoVector<Item>::at(int index) const{

if ( index > __size -1 || index < 0){
    std::cout << "Out of Index!" << std::endl;
    exit(-1);
}
else{

    return *(__array + index);
}
}



///////////////////////////////// Sorting implementation//////////////////// 

//MergeSort = true || QuickSort == false
template <typename Item>
void PseudoVector<Item>::sort(bool typesort){

// Empty guard
if(__size == 0){
    return;
}

// Re-Sort Guard
if (__isSorted){
    return;
}



if (typesort){
    mergesort::mergeSort(__array, 0, __size -1);
}

else{
    quicksort::quickSort(__array , 0 , __size -1);
}

__isSorted = true;

return ;
}




//////////////////////////////// Pushback implementation

template <typename Item>
void PseudoVector<Item>::push_back(Item itemRef){

//Size increament 
__size++;


// Block Increament
// If block reached realloc other wise do nothing 
if ( __size > __block){


    
    
    //Logarithmic memory assencion model 
    __block = (log10(__block)) * __block ;
    
    // New Heap Memory
    Item* __temp = new Item[__block];

    // Copy Previous data to heap memory
    for (int i =0; i < __size -1 ; i++){
        __temp[i] = __array[i];
    }

    // Add new element to new heap memory
    __temp[__size -1] = itemRef;


    // Avoid Memory Leak | delete previous array   
     
    delete[] __array;

    // Point array to temp new array
    __array = __temp;

    // Dot free __temp  cause it will be freed by destructor since __array points to __temp
    
}

else {

    __array[__size -1 ] = itemRef;

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
