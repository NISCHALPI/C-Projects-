#include <iostream>
#include "node.h"


////////////////////////////////SECTION: BST CLASS////////////////////////////////////////////////////////

template <typename Item>
class BST{

// Private Vars 
private:

    //head node
    __Node<Item>* head = nullptr;
        
    //size of tree
    size_t __size = 0;

    // Dublicate key 
    bool useDublicat = true;


    

///////////////////////////////////////////////////////////////SECTION:PRIVATE HELPER FUCNTIOSN///////////////////////////////////////

    // Mid Order Print 
    void __midOrder(__Node<Item>* head) const {
        if (head == nullptr){
            return;
        }
       
        __midOrder(head->leftChild);
         std::cout << head->data << " " << std::endl;
        __midOrder(head->rightChild);
        
    }

    //Insertion helper
    __Node<int>* __insertNode(__Node<Item>* parentNode, __Node<Item>* toAdd){
        
        // Base Case Linking 
        if (parentNode == nullptr){
            return toAdd;
        }

        // Less than case, left link
        else if(toAdd->data < parentNode->data){
            parentNode->leftChild = __insertNode(parentNode->leftChild, toAdd);
        }

        // Greater than, right link 
        else if (toAdd->data > parentNode->data){
            parentNode->rightChild = __insertNode(parentNode->rightChild, toAdd);
        }
        // Same Right link
        else{

            if (useDublicat){
                parentNode->rightChild = __insertNode(parentNode->rightChild, toAdd);
            }
            else{
                throw std::logic_error("Dublicate data used! Switch the attribute useDublicate!");
            }

        }   

        // Stack Relinking 
        return parentNode;

    }


    //Search helper 
    __Node<Item>* __findNode(__Node<Item>* toSearch  , Item data){
        
        // Node not Found
        if (toSearch == nullptr){
            return nullptr;
        }
        // left search    
        else if( data < toSearch->data){
            return __findNode(toSearch->leftChild , data);
        }
        // right search 
        else if (data > toSearch->data){
            return __findNode(toSearch->rightChild , data);
        }
        // found Case 
        return toSearch;
    }


    // Successor finder 
    // Args - immediate right node 
    Item __findSucessor(__Node<Item>* immediateRight){
        
        // Find the left node with nullptr
        if ( immediateRight->leftChild == nullptr){
            return immediateRight->data;
        }
        else{
           return  __findSucessor(immediateRight->leftChild);
        }

    }


    //calc height 
    int __getHeight() const ;


    // remove Node 
    __Node<Item>* __popNode(__Node<Item>* toRemove,  Item data){
        
        // Not Found case 
        if (toRemove == nullptr){
            throw std::logic_error("Removal node Not found!");
        }
        // Greater than case 
        else if (data > toRemove->data){
            toRemove->rightChild = __popNode(toRemove->rightChild, data);
        }
        // Less than case 
        else if (data < toRemove->data){
            toRemove->leftChild = __popNode(toRemove->leftChild , data);
        }
        // Remove case when no child
        else if (toRemove->isLeaf()){
            delete toRemove;
            return nullptr;
        }
        // Remove and relink the child to parent node 
        else if (toRemove->isSingle()){
            
            // Link current node 
            auto tempDown = (toRemove->leftChild != nullptr) ? toRemove->leftChild : toRemove->rightChild;
            
            // delete current node 
            delete toRemove;

            // return the below node 
            return tempDown;
        }

        // If both child exists 
        else {
            // Find sucessor data 
            auto sucessorData = __findSucessor(toRemove->rightChild);
            
            //Replace current with sucessor 
            toRemove->data = sucessorData;

            // Remove sucessor 
            toRemove->rightChild = __popNode(toRemove->rightChild, sucessorData);

        }
        // Node Return 
        return toRemove;
    }


    // pop branch 
    bool __popBranch(Item data);


public:
    

///////////////////////////////////////////////////////////////SECTION: MUTATORS///////////////////////////////////////////////////////
    
    // Add nodes in BST order
    bool addNode(Item data){
        
        // Heap Allocation
        auto toAdd = new __Node<Item>(data);
        
        try {
            head = __insertNode(head, toAdd);
            __size++; 
            return true;
        }
        catch(std::logic_error){
            
            delete toAdd;
            // Fix me 
            std::cout << "Dublicate Key Encountered" << std::endl;
            return false;
        }
        
        
    }

    // In order Print 
    void inOrder() const {
        __midOrder(this->head);
    }

    // remove Node 
    bool removeNode(Item data){
        
        // Try Removal 
        try {
            head = __popNode(head ,data);
            __size--;
            return true;
        }
        // Catch logic error of unknown Node 
        catch(std::logic_error){
            //Fix me 
            std::cout << "Cannot find Node to delete" << std::endl;
            return false;
        }
        return true;
    }

    // Search Function
    bool search(Item data)  {
        
        // found case
        auto found = __findNode(head , data);

        // Not found case 
        if ( found == nullptr){
            return false;
        }

        // return data
        return true;
        
    }


    // Add operator overload 
    friend BST<Item>& operator<<(BST<Item>& addObj ,const Item& data){
        addObj.addNode(data);
        return addObj;
    } 

    // getSize method 
    int getSize() const {return __size;}



};



int main(){

    BST<int> myBst;

    for(int i =0 ; i < 10 ; i++){

        myBst <<  rand() % 20 ;

    }

    
    // Error on head node 
    
    myBst.inOrder();
  


    return 0;
}