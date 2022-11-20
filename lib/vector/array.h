#ifndef __ARRAY_LIB__
#define __ARRAY_LIB__



//Includes Custom Libraries
#include "../../lib/sort/nlogn/mergesort.h"
#include "../../lib/sort/nlogn/quicksort.h"
#include "../../lib/search/binary.h" 
#include "../../lib/sort/n2/insersion_sort.h"


template <typename Item>
class Array{

    private:
            Item* __array ;
            size_t  __block;
            size_t  __size ;
            bool __isSorted;
            bool __sortGuard();

    public:
    
    // Rule of 3 Inmplementation

    //Default Constructer 
    Array();

    // Size Constructer
    Array(int initSize);

    // Destructer
    ~Array();

    // CopyConst 
    Array(const Array<Item>& toCopy);
    
    // Copy Assign 
    Array<Item>& operator=( const Array<Item>& toCopy);


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

    //Array
    void unique(Array& temp);

    // Pop Last 
    Item pop_back();

     // Insert Operator Overload 
    Array<Item>& operator<<(Item rhs);

    // Print Operator Overload
    template <typename Ref> 
    friend std::ostream& operator<<(std::ostream& stream , Array<Ref>& useArr );

   
};



// Copy Constructer 
template <typename Item>
Array<Item>::Array(const Array<Item>& objtoCopy){

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
Array<Item>& Array<Item>::operator=(const Array<Item>& objtoCopy){

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
Array<Item>::Array(){
    __block = 1;

    __array = new Item[__block];


    __size = 0;
    __isSorted = false;
    


}


template <typename Item>
Array<Item>::Array(int size){
    __block = size ;
    __array = new Item[size];
    __size = 0;
    __isSorted = false;



}





// Destructor
template <typename Item>
Array<Item>::~Array(){


delete[] __array;


}




// at Implementation
template <typename Item>
Item Array<Item>::at(int index) const{

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
Item Array<Item>::back() const{

    // Returns last element 
    return __array[__size -1];
}

// /////////////////////////////////////////////////Sorting and Uniqueness Section//////////////// 


// Check if __array is already Sorted
template <typename Item>
bool Array<Item>::__sortGuard(){
    
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
void Array<Item>::sort(bool useMergesort , bool useThread ){

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
void Array<Item>::push_back(Item itemRef){

//Size increament 
__size++;


// Block Increament
// If block reached realloc other wise do nothing 
if ( __size > __block){

    
    //Amortized Mem Ascension
    __block = 2 * __block ;
    
    std::cout << "Increasing Size to " << __block << std::endl; 
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


template <typename Item>
Item Array<Item>::pop_back(){

// Decrease the size
__size--;

// Store the item 
auto retVar = __array[__size];

// Re-Size condition 
if ( __size <= (__block/4)){

// Half the block
__block = __block / 2 ;

std::cout << "Decreasing Size to " << __block << std::endl; 

// Create a size of half 
auto temp = new Item[__block];

// Copy data 
for (int i= 0; i < __size ; i++){

    temp[i] = __array[i];
}

// Mem free 
delete[] __array;

// Repoint 
__array = temp;



}

return retVar;


}


// Find implementation 
template <typename Item>
int Array<Item>::find(Item toFind){

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




// Accepts a empty Array and fills it with qnique items of current object 
template <typename Item>
void Array<Item>::unique(Array<Item>& temp){

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


template <typename Item>
std::ostream& operator<<(std::ostream& stream , Array<Item>& useArr ){


for (int i =0 ; i < useArr.__size ; i++){
    stream << useArr.__array[i] << std::endl;    
}

return stream;

}

template <typename Item>
Array<Item>& Array<Item>::operator<<(Item rhs){
     
     this->push_back(rhs);
     return *this;
}

///////////////////////////////////////////////////////END OF CLASS////////////////////////////////




#endif
