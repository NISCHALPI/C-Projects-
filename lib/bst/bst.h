#ifndef __BST__LIB__
#define __BST__LIB__

// Incude Node class
#include "node.h"



////////////////////////////////SECTION: BST CLASS////////////////////////////////////////////////////////

template <typename Item>
class BST{

// Private Vars 
private:

    //head node
    __Node<Item>* head =nullptr ;
        
    //size of tree
    size_t __size = 0 ;

    // Dublicate key 
    bool useDublicat= true ;


    

///////////////////////////////////////////////////////////////SECTION:PRIVATE HELPER FUCNTIOSN///////////////////////////////////////

    // Mid Order Print 
    void __midOrder(__Node<Item>* head, std::ostream& stream) const {
        if (head == nullptr){
            return;
        }
       
        __midOrder(head->leftChild, stream);
         stream << head->data << " ";
        __midOrder(head->rightChild, stream);
        
    }

    // Pre Order Print 
    void __preOrder(__Node<Item>* head, std::ostream& stream) const {
        if (head == nullptr){
            return;
        }

        stream << head->data << " ";
        __preOrder(head->leftChild, stream);
        __preOrder(head->rightChild, stream);
        
    }

      //  Post Order 
    void __postOrder(__Node<Item>* head, std::ostream& stream) const {
        if (head == nullptr){
            return;
        }
    
        __postOrder(head->leftChild , stream);
        __postOrder(head->rightChild, stream);
        stream << head->data << " ";
        
    }



    //Insertion helper
    __Node<Item>* __insertNode(__Node<Item>* parentNode, __Node<Item>* toAdd){
        
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
    int __getHeight(__Node<Item>* currNode) const{

        // Base case if head is null return -1
        if (currNode == nullptr){
            return -1;
        }
        else {
            // Find left Height 
            int leftHeight = 1 + __getHeight(currNode->leftChild);
            // Find Right Height 
            int rightHeight = 1 + __getHeight(currNode->rightChild);
            // Reutrn max of both 
            return (leftHeight >= rightHeight) ? leftHeight : rightHeight;
        }

    }


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


    // clear recursive, like a postorder clear
    // Deletes a whole branch 
    __Node<Item>* __clear(__Node<Item>* toRemove){
        
        // If empty or nullptr
        if(toRemove == nullptr){
            return nullptr;
        }


        // Base case if leaf 
        if (toRemove->isLeaf()){
            
            // If leaf then remove  
            delete toRemove;
            
            //Decrease the size  
            __size--;

            return nullptr;

        }

        else{

            // Remove  Left and Right
            toRemove->leftChild = __clear(toRemove->leftChild);
            toRemove->rightChild = __clear(toRemove->rightChild);

            // clear Itself after remove  
            return __clear(toRemove);


        }

    } 
    
    __Node<Item>* __deepCopy(__Node<Item>* toAdd, __Node<Item>* currNode){
        
        if (toAdd != nullptr){
            throw std::logic_error("Memory Leak Possible! Pass empty pointer for deepCopy");
        }

        // Case for Leaf Pointer ptr Nothing
        if (currNode == nullptr){
            return nullptr;
        }
        else{

            //New Node linking before Preorder
            toAdd = new __Node<Item>(currNode->data);

            // Pre-Order TheData 
            toAdd->leftChild = __deepCopy( toAdd->leftChild,currNode->leftChild);
            toAdd->rightChild = __deepCopy( toAdd->rightChild ,currNode->rightChild);
            
            return toAdd;
            
        }

    }

public:
    

//////////////////////////////////////////////////////////////SECTION:RULES////////////////////////////////////////////////////////////

// Destructer
~BST(){    
        //Implement Clear and Pass head 
        __clear(head);
    
}

// Default Constructer
BST(){
    
    //head
    __Node<Item>* head = nullptr;
        
    //size of tree
    size_t __size = 0;

    // Dublicate key 
    bool useDublicat = true;

}


// Copy Constructer 
BST(BST& rhs){
    // Deep copy this shit 
    this->head = __deepCopy(this->head, rhs.head);

    // Copy Size 
    this->__size = rhs.__size;

    // Copy dublicate keys setting
    this->useDublicat = rhs.useDublicat;
    
}

// Copy Assignment Operator 
BST<Item>& operator=(const BST<Item> rhs){

    // clear The first one 
    this->head = this->__clear(this->head);

    //Deep Copy the rhs with current 
    this->head = __deepCopy(this->head, rhs.head);
    
    // Copy Size 

    this->__size = rhs.__size;

    // Copy dublicate keys setting
    this->useDublicat = rhs.useDublicat;
    
    return *this;

}


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

    // Clear Function 
    bool clear(__Node<Item>* node = nullptr) {
        
        try {

        if (node!=nullptr){
        // Clears everything
        node = __clear(node);
        }
        else {
            head = __clear(head);
        }
        }
        catch(...){
            return false;
        }

        return true;
        
        
    }

    // Add operator overload 
    friend BST<Item>& operator<<(BST<Item>& addObj ,const Item& data){
        addObj.addNode(data);
        return addObj;
    } 

//////////////////////////////////////////////////////////SECTION: ACCESSEORS////////////////////////////////////////////////////////////////
    
    // getSize method 
    int getSize() const {return __size;}
    
    // Get item binary tree
    Item getHead() const { return head->data;}

    // Get Height 
    Item getHeight() const { return __getHeight(head);}

    
    // In order Print 
    void inOrder() const {
        __midOrder(this->head, std::cout);
        std::cout << std::endl;
    }

    // Pre Order Print
    void preOrder() const {
        __preOrder(this->head, std::cout);
        std::cout << std::endl;
    }

    // Post Order
    void postOrder() const {
        __postOrder(this->head, std::cout);
        std::cout << std::endl;
    }

    // Is empty 
    bool isEmpty() const {
        return (head==nullptr) ? true: false ;
    }


};

#endif
