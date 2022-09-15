#ifndef __QUICKSORT_LIB__
#define __QUICKSORT_LIB__

//Performance 
// Best :: nlogn
// Worst :: n**2


//Imports
#include <iostream>
#include <thread>
#include <cmath>





namespace quicksort{


// The main partition function 
template <typename Item>
int __partition(Item* array, int start,  int stop){

Item pivot = array[((start + stop) / 2)];

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

int main(){





int size= 32;

   int* arr = (int*)malloc(size* sizeof(int));

   for(int i=0; i< size; i++ ){
      arr[i] = rand() % size ;
      std::cout  << arr[i] << " ";
   }

std::cout << std::endl;

quicksort::quickSort(arr, 0 , size - 1);

 for(int i=0; i< size; i++ ){
      std::cout  << arr[i] << " ";
   }

std::cout << std::endl;
return 0;
free(arr);
}
   
  

   

















#endif