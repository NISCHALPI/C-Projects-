#ifndef __QUEUE__LIB__
#define __QUEUE__LIB__


#include "list.h"



//////////////////////////////////////////////////////Queue IMPLEMENTATION///////////////////////////////////////////////////////////////////

template <typename Item>
class Queue{

    private:

        // List Underneath
        List<Item> __queue;

    public:

        // The push public method 
        void enqueue( Item toPush){ __queue << toPush;}

        // The pop method 
        Item dequeue(){
            if ( __queue.getSize() == 0){ throw std::logic_error ("Cannot Dequeue Empty Queue!");}
            return __queue.pop_front();
        }

        // The Peek method 
        Item peek(){
             if ( __queue.getSize() == 0){ throw std::logic_error ("Cannot Peek Empty Queue!");}
             return __queue.getHead()->getData();
        }

        // Is Empty Method
        bool isEmpty(){ return (__queue.getSize() == 0) ? true : false ;}
        
        // Get Length method
        int getLength(){ return __queue.getSize();}
        
        // Operator Overloads 
        // Push OvearLoad 
        friend Queue<Item>& operator<<(Queue<Item>& refQueue , Item& valAdd){
            refQueue.enqueue(valAdd);
            return refQueue;
        }
        
        // Pop Overload
        friend Queue<Item>&  operator>>(Queue<Item>& refQueue , Item& popVal){
            popVal = refQueue.dequeue();
            return refQueue;
        }

        // Print Overload 
        friend std::ostream& operator<<(std::ostream& in , Queue<Item>& refQueue){
            in << refQueue.__queue ;
            return in;
        }

};
#endif
/////////////////////////////////////////////////END OF Queue/////////////////////////////////////////////////////////////////////////////////

