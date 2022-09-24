#ifndef __MERGE_SORT_LIB__
#define __MERGE_SORT__LIB__




// Best Case: nlogn
// Worst Case:: nlogn

// Two namespace : mergesort(stable) and threaded_mergesort(unstable on HPC clusters)

#include <iostream>
#include <thread>
#include <cmath>

// Cpu count 

#ifndef __CPU__COUNT
#define __CPU__COUNT (std::thread::hardware_concurrency())
#endif


// Threading Layer calculation
#ifndef __THREADING_LAYER_ABS
#define __THREADING_LAYER_ABS

const int __THREADING_LAYER = (std::ceil(std::log2(__CPU__COUNT)));

#endif


///////////////////////////////////////////// Normal //////////////////////////////////////////////

namespace mergesort{

template <typename item>
void __merge( item* array, int& low , int mid , int& high){

// Reference for the mem address for final array copy
int i = low ;
int j =  mid + 1;


// Temporary heap memory allocated by the stack freame 
item* arrayTemp = new item[high - low + 1];

//DUMMY INDEX FOR arrayTemp
int dummyIndex = 0;


// WHO WENT FIRST  | ASSUMED FIRST WENT FIRST (i.e true)
bool whoFirst = true ;

// Merge until one is over 
// SINCE MID IS A LAST ITEM OF FIRST PART 
while (true){

if (i > mid){
   break;
}

if ( j > high){
   whoFirst = false;
   break;
}

if (array[i] < array[j]){
   arrayTemp[dummyIndex] =  array[i] ;
   dummyIndex++;
   i++;
}
else{

   arrayTemp[dummyIndex] = array[j];
   dummyIndex++;
   j++;
}

}

// ACCOUNT FOR THE REMAINING TERMS 
if (whoFirst){

   while(!(j> high)){
      arrayTemp[dummyIndex] = array[j];
      dummyIndex++;
      j++;
   }
}
else{
   while(!(i> mid)){
      arrayTemp[dummyIndex] = array[i];
      dummyIndex++;
      i++;
   }

}

// MEM COPY PART 
for (int k = 0; k < (high - low +  1); k++){
   array[k + low] =arrayTemp[ k] ;
}

delete [] arrayTemp ;
}



template <typename item>
void mergeSort(item* array, int start, int end){

// Base case upto leaf of the tree
if( start == end ){
   return;
}
// Recursive case 
else{
   // DO first half
   mergeSort(array , start , (start +end) / 2 );
   // Do second half
   mergeSort(array ,((start +end) / 2 ) + 1 , end);
   // Merge when Leaf is reached 
   __merge(array, start, ((start + end)/2 ), end );  
}  
}


}







/////////////////////////////////////////THREADED////////////////////////////////////////


// Threaded 
namespace threaded_mergesort{


template <typename item>
void __merge( item* array, int& low , int mid , int& high){

// Reference for the mem address for final array copy
int i = low ;
int j =  mid + 1;


// Temporary heap memory allocated by the stack freame 
item* arrayTemp = new item[high - low + 1];

//DUMMY INDEX FOR arrayTemp
int dummyIndex = 0;


// WHO WENT FIRST  | ASSUMED FIRST WENT FIRST (i.e true)
bool whoFirst = true ;

// Merge until one is over 
// SINCE MID IS A LAST ITEM OF FIRST PART 
while (true){

if (i > mid){
   break;
}

if ( j > high){
   whoFirst = false;
   break;
}

if (array[i] < array[j]){
   arrayTemp[dummyIndex] =  array[i] ;
   dummyIndex++;
   i++;
}
else{

   arrayTemp[dummyIndex] = array[j];
   dummyIndex++;
   j++;
}

}

// ACCOUNT FOR THE REMAINING TERMS 
if (whoFirst){

   while(!(j> high)){
      arrayTemp[dummyIndex] = array[j];
      dummyIndex++;
      j++;
   }
}
else{
   while(!(i> mid)){
      arrayTemp[dummyIndex] = array[i];
      dummyIndex++;
      i++;
   }

}

// MEM COPY PART 
for (int k = 0; k < (high - low +  1); k++){
   array[k + low] =arrayTemp[ k] ;
}

delete [] arrayTemp ;
}


template <typename item>
void mergeSort(item* array, int start, int end ,  int __THREADING =__THREADING_LAYER){
// depth means thread spawn level | i.e. depth =4, threads = 2^4
// Base case upto leaf of the tree
if( start == end ){
   return;
}
// Recursive case 
else{

   // Avoids spwaning threads after a layer 
   if ( __THREADING> 0){
   
   int mid = (start + end) / 2 ;



   //Spawn two tree branch threads 
   std::thread t1(mergeSort<item>, array , start , mid, __THREADING -1);
   std::thread t2(mergeSort<item>, array, mid + 1 , end, __THREADING-1);
   
   // Thread Join
   t1.join();
   t2.join(); 
   }
   else {
   
   // DO first half
   mergeSort<item>(array , start , (start +end) / 2, __THREADING );
   // Do second half
   mergeSort<item>(array ,((start +end) / 2 ) + 1 , end, __THREADING);

   }
   // Join after threads are finished
   __merge<item>(array, start, ((start + end)/2 ), end);  
}  
}




}
#endif



