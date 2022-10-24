#include <iostream>


#ifndef __INIT__HEAP__SIZE__
#define __INIT__HEAP__SIZE__
const int __INIT__SIZE__ = 53;
#endif 



/**@brief 
 * Made by Nischal Bhattatai
 * 
 * Templatized Heap Class 
 * Array Based Implementation 
 * Includes Heap Sorting algorithm 
 * Amortized Arrays
*/

template <typename Item>
class Heap{


//////////////////////////////////////////////////////////////////SECTION:PRIVATE///////////////////////////////////////////////////////

private:

    // Heap array   
    Item* __heapArray = nullptr;

    // Size of heap array
    size_t __size =0 ;

    // Max or Min Heap bit 
    bool __useMax;

    
    //Capacity
    int __capacity = __INIT__SIZE__;



    ////////////////////////////////////////////////////////////// PRIVATE: HELPER FUNCTION/////////////////////////////////////////////


    // Compare Function for both min and max case
    bool __compare(Item& lhs, Item& rhs) const {

        if (__useMax){
            return lhs>rhs;
        }
        else {
            return lhs<rhs;
        }
        
    }

    // Clear Helper function
    void __clear(bool __willRealloc = false){

        // Reset Size 
        __size = 0;
        __capacity = __INIT__SIZE__;

        // Delete the array
        delete[] __heapArray ;

        if(__willRealloc){
            __heapArray = new Item[__capacity];
        }


    }

////////////////////////////////////////////////////////////////////////SECTION:PUBLIC//////////////////////////////////////////////////


public:

    /////////////////////////////////////////////////////////////PUBLIC:RULES OF 3///////////////////////////////////////////////////

    //Default consturcter 
    Heap(bool useType = true){

        // Allocate Memory in the heap
        __heapArray = new Item[__capacity];

        // Use Min or Max heap  
        __useMax = useType;

    }

    //Size Construcer | Efficient 
    Heap(int size,  bool useType = true){

        //Reset capacity 
        __capacity = size;

        // Use Min max 
        __useMax = useType;

        // Allocate new capacity
        __heapArray = new Item[__capacity];

    }

    // Destructer
    ~Heap(){

        // clear the array
        __clear();

    }

    // Copy constructer 
    Heap(const Heap<Item>& src){

        // Copy initial parameters
        __size = src.__size;
        __capacity = src.__capacity;
        __useMax = src.__useMax;

        // Allocate New Heap Memory
        __heapArray = new Item[__capacity];

        // Copy all elements 
        for(size_t i = 0; i < __size ; i++){
            __heapArray[i] = src.__heapArray[i];
        }

    }

    // Copy assignment operator 
    Heap<Item>& operator=(const Heap<Item>& src){

        // Self assignment guard 
        if (this == &src){
            return *this;
        }

        // Clear With Alloc 
        __clear();

        
        // Copy initial parameters
        __size = src.__size;
        __capacity = src.__capacity;
        __useMax = src.__useMax;

        
        // Allocate New Heap Memory
        __heapArray = new Item[__capacity];

        // Copy all elements 
        for(size_t i = 0; i < __size ; i++){
            __heapArray[i] = src.__heapArray[i];
        }

        return *this;


    } 

///////////////////////////////////////////////////////////////PUBLIC: MUTATORS///////////////////////////////////////////////////////


};