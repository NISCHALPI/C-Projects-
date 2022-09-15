#include <iostream>
#include "../lib/sort/nlogn/mergesort.h"
#include "../lib/sort/nlogn/quicksort.h"

int main(){
int size = 200;
int arr[size];



for(int i = 0; i< size ; i++){
    arr[i] = rand() % (size * size);
    std::cout << arr[i] << " ";
}

std::cout << std::endl ;

threaded_quicksort::quickSort(arr, 0 , size -1);

for(int i = 0; i< size ; i++){
    std::cout << arr[i] << " ";
}

std::cout << std::endl;

}