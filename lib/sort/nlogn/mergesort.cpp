#include <iostream>
#include <thread>
#include <random>
using namespace std;

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


namespace threaded_mergesort{

void __merge( int* array, int& low , int mid , int& high){

// Reference for the mem address for final array copy
int i = low ;
int j =  mid + 1;


// Temporary heap memory allocated by the stack freame 
int* arrayTemp = new int[high - low + 1];

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






void mergeSort(int* array, int start, int end , int depth = 0){
// depth means thread spawn level | i.e. depth =4, threads = 2^4
// Base case upto leaf of the tree
if( start == end ){
   return;
}
// Recursive case 
else{

   if (depth < 4){
   int mid = (start + end) / 2 ;

   std::thread t1(mergeSort, array , start , mid, depth++ );
   std::thread t2(mergeSort, array, mid + 1 , end, depth++);
   // Thread Join
   t1.join();
   t2.join(); 
   }
   else {
   
   // DO first half
   mergeSort(array , start , (start +end) / 2, depth);
   // Do second half
   mergeSort(array ,((start +end) / 2 ) + 1 , end, depth);

   }
   // Join after threads are finished
   __merge(array, start, ((start + end)/2 ), end );  
}  
}




}





// Tests 
int main(){

   int size= 100000000;

   int* arr = (int*)malloc(size* sizeof(int));

   for(int i=0; i< size; i++ ){
      arr[i] = rand() % size ;
   }
   
   



   mergesort::mergeSort(arr, 0 , size - 1 );

  
   cout << endl;

   

}
