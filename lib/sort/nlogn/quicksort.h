#ifndef __QUICKSORT_LIB__
#define __QUICKSORT_LIB__

//Performance 
// Best :: nlogn
// Worst :: n**2


//Imports
#include <iostream>
#include <thread>
#include <cmath>


// Cpu count 
#ifndef __CPU__COUNT
#define __CPU__COUNT (std::thread::hardware_concurrency())
#endif


#ifndef __THREADING_LAYER_ABS
#define __THREADING_LAYER_ABS

const int __THREADING_LAYER = (std::ceil(std::log2(__CPU__COUNT)));

#endif

//Works with any object with comparision operator 
namespace quicksort{


// The main partition function 
template <typename Item>
int __partition(Item* array, int start,  int stop){



Item pivot = array[((start + stop) / 2 ) ];

Item temp ;

while(true){
    while(array[start] < pivot){
        start++;
    }
    while(array[stop] > pivot){
        stop--;
    }
    if(start >= stop){
        break;
    }

    temp = array[stop];
    array[stop] = array[start];
    array[start] = temp;
    start++;
    stop--;

    }


return stop;

}




template<typename Item>
void quickSort(Item* array , int start,  int end){

if (start == end){
    return ;
} 

else{

int index_low  = __partition(array, start , end);

quickSort(array , start, index_low);
quickSort(array , index_low + 1 , end);
}

}

}


// Threaded Version (Only int)
namespace threaded_quicksort{


int __partition(int* array, int start,  int stop){

int pivot = array[((start + stop) / 2)];

int temp ;

while(true){
    while(array[start] < pivot){
        start++;
    }
    while(array[stop] > pivot){
        stop--;
    }
    if(start >= stop){
        break;
    }

    temp = array[stop];
    array[stop] = array[start];
    array[start] = temp;
    start++;
    stop--;

    }


return stop;

}




void quickSort(int* array , int start,  int end,  int __THREADING =__THREADING_LAYER ){

if (start == end){
    return ;
} 

else{
int index_low  = __partition(array, start , end);

if (__THREADING > 0){

std::thread t1(quickSort,array , start, index_low, __THREADING -1);
std::thread t2(quickSort,array , index_low + 1 , end, __THREADING -1);

t1.join();
t2.join();
}

else {
    quickSort(array , start, index_low, __THREADING);
    quickSort(array , index_low + 1 , end, __THREADING);
}

}

}

}

#endif


  

   















