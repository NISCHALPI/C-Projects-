#ifndef __STACK__LIB__
#define __STACK__LIB__


#include "list.h"



//////////////////////////////////////////////////////STACK IMPLEMENTATION///////////////////////////////////////////////////////////////////

template <typename Item>
class Stack{

    private:

        // List Underneath
        List<Item> __stack;

    public:

        // The push public method 
        void push( Item toPush){ __stack << toPush ;}

        // The pop method 
        Item pop(){
            if ( __stack.getSize() == 0){ throw std::logic_error ("Cannot Pop Empty Stack!");}
            return __stack.pop_back();
        }

        // The Peek method 
        Item peek(){
             if ( __stack.getSize() == 0){ throw std::logic_error ("Cannot Peek Empty Stack!");}
             return __stack.getTail()->getData();
        }

        // Is Empty Method
        bool isEmpty(){ return (__stack.getSize() == 0) ? true : false ;}
        
        // Get Length method
        int getLength(){ return __stack.getSize();}
        
        // Operator Overloads 
        // Push OvearLoad 
        friend Stack<Item>& operator<<(Stack<Item>& refStack , Item& valAdd){
            refStack.__stack << valAdd;
            return refStack;
        }
        
        // Pop Overload
        friend Stack<Item>&  operator>>(Stack<Item>& refStack , Item& popVal){
            popVal = refStack.pop();
            return refStack;
        }

        // Print Overload 
        friend std::ostream& operator<<(std::ostream& in , Stack<Item>& refStack){
            in << refStack.__stack ;
            return in;
        }

};
#endif
/////////////////////////////////////////////////END OF STACK/////////////////////////////////////////////////////////////////////////////////

