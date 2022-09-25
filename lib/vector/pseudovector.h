#ifndef __PSEUDOVECTOR__
#define __PSEUDOVECTOR__



//Includes Custom Libraries
#include "../../lib/sort/nlogn/mergesort.h"
#include "../../lib/sort/nlogn/quicksort.h"
#include "../../lib/search/binary.h" 
#include "../../lib/sort/n2/insersion_sort.h"


template <typename Item>
class PseudoVector{

    private:
            Item* __array ;
            size_t  __block;
            size_t  __size ;
            bool __isSorted;
            bool __sortGuard();

    public:
    
    // Rule of 3 Inmplementation 
    PseudoVector();
    ~PseudoVector();
    PseudoVector(const PseudoVector<Item>& toCopy);
    PseudoVector<Item>& operator=( const PseudoVector<Item>& toCopy);


    // SECTION: ACCECORS 

    // At Implementation
    Item at( int index) const;

    Item back() const ;
    
    
    //sorting 
    void sort(bool typesort = true , bool useThreads = false);

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




// at Implementation
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



// back Inplementation
template <typename Item>
Item PseudoVector<Item>::back() const{

    // Returns last element 
    return __array[__size -1];
}

// /////////////////////////////////////////////////Sorting and Uniqueness Section//////////////// 


// Check if __array is already Sorted
template <typename Item>
bool PseudoVector<Item>::__sortGuard(){
    
    //Assumes Already Sorted
    bool __state = true ;
    int __discrepency =0;

    
    // Iterates to see if array is nearly sorted or not 
    for(int i = 1; i < __size ; i++ ){
        if ( __array[i] < __array[i -1]){
            __state = false;
            __discrepency++;
        }
    }



    // If nearly sorted, use insersion sort  
    if ( !__state && __discrepency <= int(log10(__size))){
        insersion_sort::insersionSort(__array , __size -1);
        return true;
    }
    else{
        return __state;
    }


}




//MergeSort = true || QuickSort == false
template <typename Item>
void PseudoVector<Item>::sort(bool useMergesort , bool useThread ){

// Empty guard
if(__size == 0 || __size == 1){
    return;
}


// Re-Sort Guard
if (__isSorted){
    return;
}

// Check if unsorted array happens to be already ot nearly sorted 
if (__sortGuard()){
    return ;
}


// Sort Implementation
if (useMergesort){

    if (useThread){
        threaded_mergesort::mergeSort(__array, 0, __size -1);
    }
    else{
        mergesort::mergeSort(__array, 0 , __size -1);
    }

}

else{

    if (useThread){
        threaded_quicksort::quickSort(__array, 0, __size -1);
    }
    else{
        quicksort::quickSort(__array, 0 , __size -1);
    }

}

__isSorted = true;

return ;

}




//// Logistic Pushback implementation
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


// Not Sorted after Pushback
if (__isSorted){
    __isSorted = false;
}


}




// Find implementation 
template <typename Item>
int PseudoVector<Item>::find(Item toFind){

    // If Not Sorted, do linear search
    if (!__isSorted){
        for(int i=0; i< __size ; i++){

            if( __array[i] == toFind){
                return i;
            }

        }
        return -1;
    }
    else{
        
        // Do to Binary Search
        return binary_search::binarySearch(__array , toFind , 0 , __size -1);
    }



}




// Accepts a empty pseudovector and fills it with qnique items of current object 
template <typename Item>
void PseudoVector<Item>::unique(PseudoVector<Item>& temp){

    // Add first 
    temp.push_back(__array[0]);



    if (!this->__isSorted){
        
        // If parent not sorted implement, approx ~ O(n*no_of_uniq) algorithm  
        for (int i =1; i< __size ; i++){

            // If not found in temp array, append in temp array
            // Works for unsorted array
            if (temp.find(__array[i]) == -1){
                temp.push_back(__array[i]);
            }
        
        }
    
    }

    else {
        // n algorithm to find unique in sorted array 
        // The unique are also sorted
       for (int i =1; i< __size ; i++){

            // If not equal to last element in temp, do pushback
            if ( __array[i] != temp.back() ){
                temp.push_back(__array[i]);

            }
        }

        // Finally the unique array will also be sorted because parent array will also be sorted 
        temp.__isSorted = true;

    }

    
}




///////////////////////////////////////////////////////END OF CLASS////////////////////////////////




#endif
