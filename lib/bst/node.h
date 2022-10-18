#ifndef __BST_NODE_LIB
#define __BST_NODE_LIB




/////////////////////Node Class/////////////////////////////////////////////////////////////////////////////////////////


// Forward Decleration

template <typename Item>
class BST;



template <typename Item>
class __Node{
private:
    __Node* leftChild;
    __Node* rightChild;
    Item data;
    bool ishead = false;
    


public:

    //Constructer
    __Node(Item data, __Node<Item>* leftChild = nullptr ,__Node<Item>* rightChild = nullptr  ){

        this->leftChild = leftChild;
        this->rightChild = rightChild;
        this->data = data;
    }

     






    // Leaf and Head 
    bool isHead() const {return ishead;}
    bool isLeaf() const {return (leftChild == nullptr && rightChild==nullptr);}

    // single parent 
    bool isSingle() {return (!isLeaf() && (leftChild== nullptr || rightChild ==nullptr)) ? true : false;}

    // Firend a class 
    template <typename type>
    friend class BST;

};
#endif
//////////////////////////////////////////////////////////END OF NODE CLASS////////////////////////////////////////////////////////////



