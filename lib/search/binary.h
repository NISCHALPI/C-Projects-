#ifndef __BINARY_SEARCH_LIB__
#define __BINARY_SEARCH_LIB__


namespace binary_search{


//Works on sorted array
// Returns index if found else 
template <typename Item>
int binarySearch(Item* array , Item findItem ,int start ,int end){

    //Declare Mid
    int mid;

   // Until start less than or equal to end  
   while (start <= end) {

      mid = (start + end) / 2;

      if (array[mid] < findItem) {
         start = mid + 1;
      }
      else if (array[mid] > findItem) {
         end = mid - 1;
      }
      else {
         return mid;
      }
   }
   
   //If not returned yet, not found
   return -1;
}

}

#endif