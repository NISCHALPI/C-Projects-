#ifndef __PQUEUE__LIB__
#define __PQUEUE__LIB__
#include "heap.h"

/**@brief 
 * Made by Nischal Bhattatai
 * 
 * Templatized Priority Queue Class 
 * Heap Based Implementation
 * Set priority while enqueing or Pass a priority lambda function on the constructer
 * Lowest Number Gets Highest Priority, 0 is higher than  1
 * Won't work for negative 
*/


// Node Class 
template <typename Item>
class __pNode{
    public:
        Item data;
        size_t priority=INT32_MAX;
        

        // Default Constructer
        __pNode(){
            data = Item();
            priority = priority=INT32_MAX;
            
        }
        
        // Data Constructer 
        __pNode(Item data){
            this->data = data;
        }

        // Priority and data Constructer 
         __pNode(Item data, size_t priority){
            this->data = data;
            this->priority = priority;
        }

        // Operator Overloads 
        bool operator>(__pNode<Item>& rhs ){
            return (this->priority < rhs.priority); 
        }
        bool operator<(__pNode<Item>& rhs ){
            return (this->priority > rhs.priority); 
        }

};
 

// Priority Queue Class
template <typename Item>
class pQueue{


//////////////////////////////////////////////////////SECTION: PRIVATE////////////////////////////////////////////
private:
    // Base Heap
    Heap<__pNode<Item>> __priorityHeap;
    
    // int Func(Object) -- Priority Mapping function if user have it !
    size_t (*pfuncptr) (Item) = nullptr;

    bool hasMapping = false;

//////////////////////////////////////////////////////SECTION: HELPER FUNC////////////////////////////////////////////



//////////////////////////////////////////////////////SECTION: PUBLIC//////////////////////////////////////////////////

public:

    // Default Constructer 
    pQueue(){
        pfuncptr = nullptr;
        hasMapping = false;
    }

    // Priority fucntion Constructer 
    pQueue(size_t (*pfuncptr) (Item)){
        this->pfuncptr = pfuncptr;
        hasMapping = true;
    }

    // Copy Constructer 
    pQueue(pQueue<Item>& src){
        this->hasMapping = src.hasMapping;
        this->pfuncptr = src.pfuncptr;
        this->__priorityHeap = src.__priorityHeap;
    }

    // Copy Assignment Operator 
    pQueue<Item>& operator=(pQueue<Item>& src){
        
        // Self Assignment Guard 
        if (this == &src){
            return *this;
        }

        this->hasMapping = src.hasMapping;
        this->pfuncptr = src.pfuncptr;
        this->__priorityHeap = src.__priorityHeap;

        return *this;
    }

    // Enqueue 
    void enqueue(Item data){
        
        // If no map Func, throw Error 
        if(!hasMapping){
            throw std::logic_error("No Priority Function Passed in constructer! Pass Priority");
        }

        // Add to heap
        __priorityHeap << __pNode<Item>(data, pfuncptr(data));
        
        return;
    }

    // Enqueue 
    void enqueue(Item data, size_t priority){

         // Add to heap
        __priorityHeap << __pNode<Item>(data, priority);
        
        return;

    }

    // Dequeue 
    Item dequeue() {
        return __priorityHeap.pop_front().data;
    }

    // Peek
    Item peek() {
        return __priorityHeap.__heapArray[0].data;
    }

    // Size
    int getSize() const {
        return __priorityHeap.getSize();
    }
    
    // Check if Empty
    bool isEmpty() const {
        return (getSize() == 0) ? true : false;
    }




};

#endif
