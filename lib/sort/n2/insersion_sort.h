#ifndef __INSERSION_SORT_LIB__
#define __INSERSION_SORT_LIB__

// Runtime complexiy is O(N) for nearly sorted array

#include <iostream>

//Template for Selection Sort
// Big O order = O(n^2)
template <typename Compare>
void insersionSort(Compare* refList, size_t size){


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


//Proceed if everything is in order

size_t sortedIndex = 1;
size_t reverseIndex = 0;
size_t currentIndex = 0 ;

Compare temp;

 
for (sortedIndex ; sortedIndex < size;  sortedIndex++){

    reverseIndex = sortedIndex - 1;

    currentIndex = sortedIndex;

    while(reverseIndex  != -1){
        
        if (refList[reverseIndex] < refList[currentIndex])
        break;

        temp  = refList[currentIndex] ;
        refList[currentIndex] = refList[reverseIndex];
        refList[reverseIndex] = temp ;
        

        reverseIndex--;
        currentIndex--;

    }

}
}


//INTEGER TEST VECTOR PASSED

#endif