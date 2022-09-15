#ifndef _SELECTION_SORT_LIB_
#define _SELECTION_SORT_LIB_

#include <iostream>


//Template for Selection Sort
// Big O order = O(n^2)
template <typename Compare>
void selectionSort(Compare* refList, size_t size){


//Check if there are enough data
if (!(size > 1)){
    throw std::invalid_argument("Size is not greater than 1! Nothing to sort");
}


//Check if comparison operater is overloaded for the data-type
try{
    (refList[0] < refList[1]);
}
catch(...){
    throw std::invalid_argument("Operater( < ) not defined for the data type");

}


// Temp variable decleration
size_t min;
Compare temp;

// Acending Sort
//Proceed if everything is defined
for(size_t i = 0; i < size - 1 ; i++){

min  = i ;

for(size_t j = i + 1 ; j < size; j++){

if (refList[j] < refList[min]){
    
    min = j;

}

}

// Swap current with the lowest
temp = refList[i];

refList[i] = refList[min];

refList[min] = temp;


}


}


// Integer and Char Test Vector Passed

#endif
