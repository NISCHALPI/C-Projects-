#ifndef __HEAP__LIB__
#define __HEAP__LIB__


#include <iostream>

/**@brief 
 * Made by Nischal Bhattatai
 * 
 * Templatized Heap Class 
 * Array Based Implementation 
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
    int __capacity = 1;



    ////////////////////////////////////////////////////////////// PRIVATE: HELPER FUNCTION/////////////////////////////////////////////


    // Compare Function for both min and max case
    bool __compare(int lhs, int rhs) const {

        if (__useMax){
            return __heapArray[lhs]>__heapArray[rhs];
        }
        else {
            return __heapArray[lhs]<__heapArray[rhs];
        }
        
    }

    // Clear Helper function
    void __clear(bool __willRealloc = true){

        // Reset Size 
        __size = 0;
        __capacity = 1;

        // Delete the array
        delete[] __heapArray ;

        if(__willRealloc){
            __heapArray = new Item[__capacity];
        }


    }

    // Amortized Resize 
    void __resize() {

        // Reize Up condition
        if(__size == __capacity){

            
            // Double Capacity 
            __capacity *= 2;

            
            // New Array
            auto __tempHeap = new Item[__capacity];

            // Recopy the data
            for(int i = 0 ; i < __size; i++){

                __tempHeap[i] = __heapArray[i];

            }

            // Memory Clean
            delete [] __heapArray;

            // Reassignment 
            __heapArray = __tempHeap;
        }
        
        // Resize Down Condition 
        else if(__size <= __capacity/4){

            // Make it half 
            __capacity = __capacity/ 2;

            
            //new Array
            auto __tempArray = new Item[__capacity];

            // Copy data
            for(int i = 0 ; i < __size ; i++){
                __tempArray[i] = __heapArray[i];
            }

            // Mem Free
            delete[] __heapArray;
            
            // Copy
            __heapArray = __tempArray; 
        }
    
        return;
    }  





    // Percolation
    void __swap(int a, int b){

        if ( a >= __size || b >= __size || a < 0 || b <0){
            throw std::logic_error("Out of index Access!");
        }

        auto temp = __heapArray[a];
        __heapArray[a] = __heapArray[b];
        __heapArray[b] = temp;

    }

    // Down Percolation
    void __percolateDown(int index){

        // Base Case 
        if ( (2* index + 1) >= __size){
            return;
        } 

        // Second Base - if second child out of rannge 
        if ((2*index +2) >= __size){
            
            // Compare Left
            if (__compare(2*index +1 ,index)){
                __swap(index , 2* index +1);
            }
            
            return;
        } 

        

    // Compare Left and Right First
         if (__compare(2*index +1 , 2 * index + 2)){
                 
                // Compare and swap with left
                if (__compare(2*index +1 , index)){
   
                    __swap(index, 2*index +1);
                    __percolateDown(2*index +1);
                }
               
            
            }
            else {
                   // Compare Right and swap with left
                if (__compare(2*index +2, index)){
                    __swap(index, 2*index +2);
                    __percolateDown(2*index +2);
                }

            }
           
             
        
    }

    // Up percolation
    void __percolateUp(int index) {

        // Base Case 
        if ( index < 0){
            return;
        }
        else {
            int parent = (index -1) /2 ;

            if (__compare(index , parent)){
                __swap(index , parent);
                __percolateUp(parent);
            }

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


    // Destructer
    ~Heap(){

        // clear the array
        __clear(false);

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

        // Clear Without Alloc 
        __clear(false);

        
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

    // PushBack Implementation
    void push_back( Item data) {

        //Increse Size 
        __size++;
        // Check Resize 
        __resize();
        __heapArray[__size -1] = data;

        // Percolate Up 
        __percolateUp(__size -1);

    }

    // Get Front of the heap
    Item pop_front (){ 

        if (__size == 0){
            throw std::logic_error("Cannot pop an empty heap");
        }
        
        // Store front
        auto Temp = __heapArray[0]; 

        // Swap, percolation and Resize         
        __swap(0,__size-1);

        //Decrease Size 
        __size--;

        __percolateDown(0);
        __resize();

        return Temp;
        


    }





//////////////////////////////////////////////////////////////PUBLIC: ACESSORS////////////////////////////////////////////////////

//print heap
    void print(std::ostream& stream = std::cout) const {

        for(int i =0 ; i < __size ; i++){
            stream << __heapArray[i] << " ";
        }
    }

// get Size 
    int getSize() const {
        return __size;
    }


/////////////////////////////////////////////////////////////PUBLIC: OVERLOADS///////////////////////////////////////////

friend Heap<Item>& operator<<(Heap<Item>& src, Item data){
    src.push_back(data);
    return src;
}

friend Heap<Item>& operator>>(Heap<Item>& src, Item data){
    data = src.pop_front(data);
    return src;
}

friend std::ostream& operator<<(std::ostream& stream , Heap<Item>& src){
    
    src.print(stream);
    
    return stream;
}

};

#endif

