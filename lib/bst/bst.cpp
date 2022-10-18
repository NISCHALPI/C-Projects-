#include <iostream>
#include "node.h"


//////////////////////////////////////////////////////////////SECTION: BST CLASS////////////////////////////////////////////////////////

template <typename Item>
class BST{

// Private Vars 
private:

    //head node
    __Node<Item>* head;
        
    //size of tree
    size_t __size;

    // Dublicate key 
    bool useDublicat = true;
    

///////////////////////////////////////////////////////////////SECTION:PRIVATE HELPER FUCNTIOSN///////////////////////////////////////

  // Mid Order Print 
    void midOrder(__Node<Item>* head) const {
        if (head == nullptr){
            return;
        }
        midOrder(head->leftChild);
        std::cout << head->data << " " << std::endl;
        midOrder(head->rightChild);
        
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
    bool __findNode(Item data);

    //calc height 
    int __getHeight() const;

    // remove Node 
    bool __popNode(Item data) ;

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
            return true;
        }
        catch(std::logic_error){
            
            delete toAdd;
            // Fix me 
            std::cout << "Dublicate Key Encountered" << std::endl;
            return false;
        }
        
        
    }


    void inOrder() const {
        midOrder(this->head);
    }

  




    // Add operator overload 
    friend BST<Item>& operator<<(BST<Item>& addObj ,const Item& data){
        addObj.addNode(data);
        return addObj;
    } 





};



int main(){

    BST<int> myBst;

    for(int i =0 ; i < 10 ; i++){

        myBst << i;

    }

    myBst.inOrder();
    


    return 0;
}