#include <iostream>
#include <fstream>
#include <list>
#include <string>



using namespace std;


template <typename Item>
class __Node{

public:
    __Node* leftChild;
    __Node* rightChild;
    Item data;

        

    //Constructer
    __Node(Item data= Item(), __Node<Item>* leftChild = nullptr ,__Node<Item>* rightChild = nullptr  ){

        this->leftChild = leftChild;
        this->rightChild = rightChild;
        this->data = data;
    }

    

    // Check Leaf
    bool isLeaf() const {return (leftChild == nullptr && rightChild==nullptr);}

    // single parent 
    bool isSingle() {return (!isLeaf() && (leftChild== nullptr || rightChild ==nullptr)) ? true : false;}

};


// Alias
typedef __Node<int> Node;





// Open Func
template <typename Item>
list<Item> read(string filename){

    list<Item> readList;

    fstream inFile(filename);

    if (!inFile.is_open()){
        cout << "Cannot open " << filename << "file" << endl;
        exit (-1); 
    }

    Item temp =0 ;

    while(true){

        if (inFile.eof()){
            break;
        }

        inFile >> temp ;
        readList.push_back(temp);
    } 

    inFile.close();

    return readList;
}


// Splitter
list<int> split(int splitNode, list<int>& splitList){

    list<int> returnList;

    int size = 0;

    int temp;
    size = splitList.size();

    for (int i =0 ; i<size; i++){
        temp =splitList.front();
        splitList.pop_front();

        
        if (temp == splitNode){
            break;
        }

        returnList.push_back(temp);

    }

    return returnList;



}


void printList(list<int> toPrnt){

    int size = toPrnt.size();
    cout << " ";
    for(int i=0; i < size ; i++){
        cout << toPrnt.front() << " ";
        toPrnt.pop_front();
    }

}


// Wrapper Class
class Wrapper{

public:    
    Node* refNode;
    list<int> inorderLeft;
    list<int> inorderRight;

    Wrapper(){

    }

    Wrapper(Node* refNode, list<int> inorderLeft, list<int> inorderRight){
        this->refNode = refNode;
        this->inorderLeft = inorderLeft;
        this->inorderRight = inorderRight;
    }

    void print() {
        cout << "Q |" << refNode->data;
        printList(inorderLeft);
        cout << " | ";
        printList(inorderRight);
        cout << endl;
    }

};


// Make Tree Func
Node* makeTree(list<int>& inorder, list<int>& levelorder){

    // Heap Head
    Node* headPtr = new Node(levelorder.front());
    levelorder.pop_front();

    list<int> tempList;

    // Wrapper Queue 
    list<Wrapper> warpperQueue;

    tempList = split(headPtr->data, inorder);
    // Inti Queue 
    warpperQueue.push_back(Wrapper(headPtr, tempList, inorder));



    //Temp vars
    Wrapper tempWrap;
    Node* newNode;
    

    // Linking Phase
    while(!levelorder.empty()){
        
        // Take out the node 
        tempWrap = warpperQueue.front();
        warpperQueue.pop_front();

       
        //tempWrap.print();

        if (!tempWrap.inorderLeft.empty()){
            
        
            newNode = new Node(levelorder.front());
            levelorder.pop_front();


            // Link Left 
            tempWrap.refNode->leftChild = newNode;

            tempList = split(newNode->data, tempWrap.inorderLeft);
            warpperQueue.push_back(Wrapper(newNode,tempList, tempWrap.inorderLeft));
        }

        if (!tempWrap.inorderRight.empty()){
           
            newNode = new Node(levelorder.front());
            levelorder.pop_front();

            

            //Link Rignt
            tempWrap.refNode->rightChild = newNode;
            
            tempList = split(newNode->data, tempWrap.inorderRight);

            warpperQueue.push_back(Wrapper(newNode, tempList, tempWrap.inorderRight));


            
        }



    }
    
    
    return headPtr;



}


void inorder(Node* head){

    if (head == nullptr){
        return;
    }
    else {
        inorder(head->leftChild);
        cout << head->data << endl;
        inorder(head->rightChild);
    }
}



void decode(Node* head, Node* currNode, list<char>& decodeList){
    
    // Base Case 
    if (decodeList.empty()){
        return;
    }

    if (currNode->isLeaf()){
        cout << char(currNode->data) ;
        decode(head, head, decodeList);
    }
    else {
        
        char dir = decodeList.front();
        decodeList.pop_front();

        if (dir == '0'){
            decode(head , currNode->leftChild, decodeList);
        }
        else if (dir == '1'){
            decode(head , currNode->rightChild, decodeList);
        }
    }
    


}

void freeTree(Node* head){

    if (head == nullptr){
        return;
    }
    else {
        freeTree(head->leftChild);
        freeTree(head->rightChild);
        delete head;
    }
}


int main(int argc, char** argv){

    if (argc !=4){
         cout << "Not enough Args!" << endl;
         exit (-1);
    }

    // Read Files 
    list<int> inOrder = read<int>(argv[1]);
    list<int> levelOrder = read<int>(argv[2]);
    list<char> encodedMessage = read<char>(argv[3]);    

    

    Node* head = makeTree(inOrder, levelOrder);
    
    decode(head, head, encodedMessage);


    freeTree(head);

    return 0;

}


