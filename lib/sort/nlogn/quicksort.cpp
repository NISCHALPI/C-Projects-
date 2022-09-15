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
#define __CPU__COUNT (std::thread::hardware_concurrency())

// Threading Layer calculation
const int __THREADING_LAYER = (std::ceil(std::log2(__CPU__COUNT))) ;


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

int main(){





int size= 100000000;

   int* arr = (int*)malloc(size* sizeof(int));

   for(int i=0; i< size; i++ ){
      arr[i] = rand() % size ;
   }

std::cout << std::endl;

threaded_quicksort::quickSort(arr, 0 , size - 1);


std::cout << std::endl;
free(arr);
return 0;

}
   
  

   















