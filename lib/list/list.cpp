#include <iostream>
#include <stdexcept>
#include "../vector/pseudovector.h"




// Forward Decleration
template<typename Item>
class List;


template<typename Item>
class Node{
    
    private:
        Item data;
        Node<Item>* front;
        Node<Item>* back;
        int index;
        
        

    public:
        
        // Default Constructor 
        Node(){
            index =INT16_MAX;
            data = INT16_MAX;
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

            throw std::logic_error("Cannot Copy Node! False Call");
        }

        // Copy Assignment Operator 
        Node& operator=(const Node& toCopy){

            throw std::logic_error("Cannot Copy Node! False Call");

        }

        // Is head or Tail
        bool isHead() const{
            return (index == -1) ? true : false ;
        }

        bool isTail() const{
            return (index == -2) ? true : false ;
        }

        Item getData() const {
            return data;
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
        
        
        // Linear Search Function
        Node<Item>* __search(Item data){
            
            auto temp = getHead();

            while(!temp->isTail()){
                
                if(temp->data == data){
                    return temp;
                }

                temp = temp->back;
            }

            return nullptr;

        }

        // Add Node Private Func
        void __addNode(Node<Item>* previous , Item data){
        
        // New Heap Node
        Node<Item>* toAdd = new Node<Item>(data);
        
        // Pointer Linking | 4 Way linking 
        toAdd->front = previous;
        toAdd->back = previous->back;
        previous->back->front = toAdd;
        previous->back = toAdd;

        toAdd->index = __size;
        
        return;
       }
    
        // Abstract removal operation
        void __removeNode(Node<Item>* removalNode){

            if (removalNode->isHead() || removalNode->isTail()){
                throw std::logic_error("Removing the dummy node is not allowed"); 
            }

            // Relinking Linking
            removalNode->back->front = removalNode->front;
            removalNode->front->back = removalNode->back; 

            __size--;

            // Need to free Node 
            delete removalNode;
            
        } 

    
    public:



///////////////////////////////////SECTION: RULE OF 5 /////////////////////////
       
        // Default
        List(){
            
            head = new Node<Item>;
            tail = new Node<Item>;

            __size = 0;

            head->index = -1;
            tail->index = -2;

            // Initial Linking
            head->back = tail;
            tail->front = head;
            
            
        }

        // Item Constructor
        List(Item data){
            
            head = new Node<Item>;
            tail = new Node<Item>;

            __size = 0;

            head->index = -1;
            tail->index = -2;

            // Initial Linking
            head->back = tail;
            tail->front = head;
            
            //Font Push
            push_front(data);
        }
    
        // Copy Constructer
        List(const List& toCopy){
            
            head = new Node<Item>;
            tail = new Node<Item>;

            __size = 0;

            head->index = -1;
            tail->index = -2;

            // Initial Linking
            head->back = tail;
            tail->front = head;
            
            Node<Item>* temp = toCopy.head->back;


            while(!temp->isTail()){

                push_back(temp->data);
                temp = temp->back;
            }



        }

        // Destructor
        ~List(){
            
            while(head->back != nullptr){
                head = head->back;
                delete head->front; 
            }
            
            delete head;
         
        }


        


//////////////////////////////////SECTION: MUTATORS ////////////////////////////
 
       
       
        // push_back implementation
        void push_back(Item data){
           
           // Add Node after tail 
            __addNode(tail->front, data);
            __size++;
         

        }

        
        // push_front Implementation 
        void push_front(Item data){
          
          // Add Node after head
          __addNode(head, data);
          __size++;

        }


/////////////////////////////////SECTION: REMOVERS ///////////////////////////////////////



        // Clear operation
        void clear() {

            Node<Item>* temp = head->back;

            while(!temp->isTail()){
                temp = temp->back;
                __removeNode(temp->front);
            }

        }


        // Copy Assignment operators
        List<Item>& operator=(const List<Item>& srcToCopy){
            
            // Recopy Guard
            if (this == &srcToCopy){
                return *this;
            } 

            // Clear Guard
            this->clear();

            // Temp
            Node<Item>* temp = srcToCopy.head->back;

            // Loop Copy
            while(!temp->isTail()){

                push_back(temp->data);
                temp = temp->back;
            }

            // Reutrns Ref
            return *this;


        } 


        // remove first Operator 
        Item pop_front(){
            
            // Temp 
            Item temp;
            
            // Get Head 
            auto firstElement = getHead();

            // Get data 
            temp = firstElement->data;

            // Remove first 
            __removeNode(firstElement);

            return temp;


        }


        

/////////////////////////////////////SECTION: ACESSORS///////////////////////////////
        
        // Getters 
        Node<Item>* getHead(){

            if (__size == 0){
                throw std::logic_error("No head Exists! Size = 2");
            }

            return head->back;
        }

         // Getters 
        Node<Item>* getTail(){

            if (__size == 0){
                throw std::logic_error("No Tail Exist! Size=0");
            }

            return tail->front;

        }

        // Data Print from Head 
        void print_head(std::ostream& out) const{
            
            Node<Item>* temp = head->back;

            while(!temp->isTail()){

                out <<  temp->data << std::endl; 
                temp = temp->back;

            }

            
        }

        // Data Print from tail
        void print_tail(std::ostream& out) const{
            
            auto temp = tail->front;

            while(!temp->isHead()){

                out <<  temp->data << std::endl; 
                temp = temp->front;

            }
        }
        
        // << operator overload
        friend std::ostream& operator<<(std::ostream& inStream, List& src){

            src.print_head(inStream);
            return inStream;
        }


};



int main(){

    
    List<int> testList;



    return 0;
    
}
