#include <iostream>
#include <stdexcept>
#include "../vector/pseudovector.h"

using namespace std;


// Define Key Size 
#if !defined(__KEYSIZE)
#define __KEYSIZE 5
#endif // __KEYSIZE



// Forward Decleration
template<typename Item>
class List;


template<typename Item>
class Node{
    
    private:
        Item data;
        Node* front;
        Node* back;
        size_t index;
        
        

    public:
        
        // Default Constructor 
        Node(){
            index =NULL;
            data = NULL;
            front = nullptr;
            back = nullptr;
        }

        // Data Constructor 
        Node(Item initData){
            this->data = initData;
            this->front = nullptr;
            this->back = nullptr;
            index = 0;
        }
        
        // Copy Constructor 
        Node(const Node& toCopy){

            throw logic_error("Cannot Copy Node! False Call");
        }

        // Copy Assignment Operator 
        Node& operator=(const Node& toCopy){

            throw logic_error("Cannot Copy Node! False Call");

        }

        // Friend                --- Template Parameter has to  be different
       template<typename Ref>
       friend class List;
 
};


template<typename Item>
class List{

    private:
        
        Node<Item>* head;
        Node<Item>* tail;
        size_t __size;

        // Mapping The Items 
        PseudoVector<Node<Item>*> map;
        
        


    public:



///////////////////////////////////SECTION: RULE OF 5 /////////////////////////
       
        // Default
        List(){
            head = nullptr;
            tail = nullptr;
            __size = 0;
        }

        // Item Constructor
        List(Item data){
            head = new Node<Item>(data);
            tail = head;
            __size = 1;
        }

        // Destructor
        ~List(){
            
           // Checks if head is not empty 
           if (head != nullptr){
            
            
            // Until last node 
            while(head->back != nullptr){
                head = head->back;
                delete head->front;
            }   

            //delete Last Node itself 
            delete head;
           }
            
        }

        // Copy Constructer
        List(const List& toCopy){
            
            // Default wont get called
            this->head = nullptr;
            this->tail = nullptr;
            this->__size = 0;

            for(Node<Item>* currIndx = toCopy.getHead(); currIndx != nullptr; currIndx = currIndx->back){
                this->push_back(currIndx->data);
            }


        }

        // Copy Assignment Operator 
        List& operator=(List& toCopy){
            
            // Self Assignment Guard
            if(this == &toCopy){
                return *this;
            }
            
            // Free if already there ,apply destructor
            if (this->head != nullptr){
                // Until last node 
                while(!head->back){
                    head = head->back;
                    delete head->front;
                }   

                //delete Last Node itself 
                delete head;

            }
 

            // Reinitialze private variables
            this->head = nullptr;
            this->tail = nullptr;
            this->__size = 0;

            // Copy new data 
            for(Node<Item>* currIndx = toCopy.getHead();currIndx != nullptr; currIndx = currIndx->back){

            this->push_back(currIndx->data);
            
            }

            return *this;
            
        }






//////////////////////////////////SECTION: MUTATORS ////////////////////////////
 
        // push_back implementation
        void push_back(Item data){
           
            
            // Generate New Node 
            Node<Item>* newNode = new Node<Item>(data);
            
            
            // Size Guard
            if (__size== 0){
                head = newNode;
                tail = head ;
                __size++;
                return;
            }

            // If size is not 0
            tail->back = newNode ;
            newNode->front = tail;
            tail = newNode;

            // Increment Size 
            __size++;

            if (__size % __KEYSIZE == 0){
                map.push_back(newNode);
            }

        }

        
        // push_front Implementation 
        void push_front(Item data){

           // New Node to Link 
           Node<Item>* newNode = new Node<Item>(data);
          
          // Link the new Node back to new Head 
           newNode->back = head;
           
          // If Head not Empty link, previous frot to back
           if( head != nullptr){
            head->front = newNode;
           }

           //  Move the firs Node 
           head = newNode;

           // Increament Size 
           __size++;

        }


        void at(size_t acessIndex){

            if (acessIndex < 0 || acessIndex > __size -1 ){
                throw out_of_range("Out of range acess!");
            }

            size_t mapIndex = acessIndex / __KEYSIZE;
            size_t offSet = acessIndex % __KEYSIZE ;


        }


    


/////////////////////////////////////SECTION: ACESSORS////////////////////////

        // Data Print from Head 
        void print_head() const{
            
            for(Node<Item>* currNode = head; currNode != nullptr ; currNode= currNode->back){

                cout << currNode->data << endl;
            }
        }

        // Data Print from tail
        void print_tail() const{

            for(Node<Item>* currNode = tail; currNode != nullptr; currNode = currNode->front){
                cout << currNode->data << endl;
            }

        }


        // Size Accessor 
        int getSize() const{
            return __size;
        }

           // Get Head Node 
        Node<Item>* getHead() const {
            return head;
        }

        // Get Tail Node 
        Node<Item>* getTail() const {
            return tail;
        }

        // Fix Me -- Delete Me 
        void print_map() const {

            for(size_t i = 0; i < map.getSize() ; i++)

                cout << map.at(i)->data << endl;
            }
};



int main(){
    
    List<int> list;

    for(int i =0 ; i< 100 ; i++){
        list.push_back(i);
    }
    
    
     

    return 0;
    
}
