#ifndef _IDENTIFIER_H
#define _IDENTIFIER_H

#include <iostream>
#include <string>

using namespace std;


// Temp struct | Read data into this thing
typedef struct tempID{

string name1;
string name2;
int a2b;


}tempID;





////////////////////////////////////////////////////////////////////////IDENTIFIER CLASS DEF//////////////////////////////////////////////////////////////////////////////////////////////////////////


class Identifier{

public:
    //Constructer
    Identifier(string name);
    
    // Varaible declaration 
    string name ="" ;   // lower only
    int from = 0;
    int to = 0 ;
    bool isLeaf = false;
    
    // Method Declaration 
    
    // returns the ratio of to/from double
    double GetRatio();
    
    bool CheckLeaf();

};

//Constructer 
Identifier::Identifier(string name){

    this->name = name;
}

//Ratio Implementation 
double Identifier::GetRatio(){
    if (from =! 0){
    
    return (double)to/from; 

    }
    else{
        return -1 ;
    }
}

//Check Leaf Implementation
bool Identifier:: CheckLeaf(){
    
    if ( (to == 0 && from != 0) || (to != 0 && from == 0) ){
        return true ;
    }
    
    return false; 

}

////////////////////////////////////////////////////////////////////////SUPER VECTOR CLASS DEF//////////////////////////////////////////////////////////////////////////////////////////////////////////

class SuperIdentifier{

private:
    Identifier* idList;

public:
    
    
    //Constructer 
    SuperIdentifier();
    
    //Dectructor
    ~SuperIdentifier();
    
    // size of idList
    int size; 
    
    // methods 
    void push_back(Identifier temp);
    

    // at method 
    Identifier* at(int i);    

    //Access methods
    int where(string name) const;


    // see if name already exists 
    bool hasObject(string name) const;





    SuperIdentifier& operator<<(tempID ID); 

    
};

// Constructer Implementation
SuperIdentifier::SuperIdentifier(){

    idList = (Identifier*) malloc(sizeof(Identifier));
   

    size = 0 ;

}


//Destructor Implementation
SuperIdentifier::~SuperIdentifier(){

    free(idList);
}

// Add to the list
void SuperIdentifier::push_back(Identifier temp){
    if (size==0){
        *idList = temp;

        size = size + 1;
    }

    else {
        size +=1 ;
        idList = (Identifier*)realloc(idList, size * sizeof(Identifier));

        *(idList + size -1) = temp; 
       


    }

}


// where(i) method 
int SuperIdentifier::where(string name) const{
    for (int i = 0 ; i<size; i++){

        if ((idList+i)->name == name){
            return i;
        }
    }
    return -1 ;
}

// at method - > returns  a reference 

Identifier* SuperIdentifier::at(int i){


if (i> -1 &&  i < size){
    
    return (idList + i);
}

else{

    throw "Out of Index";
}
}


// checks if the vector already has the item
bool SuperIdentifier::hasObject(string name) const{
    
    
    for (int i=0; i<size; i++){
        if ( (idList + i)->name == name){
            return true ;
        }

    }

    return false;

}


SuperIdentifier& SuperIdentifier::operator<<(tempID ID){

    int firstIndex = this->where(ID.name1);
    int secondIndex = this->where(ID.name2);

    

    if ( firstIndex !=  -1){
        (idList + firstIndex)->from += ID.a2b ;
        
    }
    else {
        Identifier youngeBlood(ID.name1);
        youngeBlood.from += ID.a2b ;

        this->push_back(youngeBlood);
    }

    if (secondIndex != -1){
        (idList + secondIndex)->to += ID.a2b ;
    }
    else {
        Identifier youngeBlood(ID.name2);
        youngeBlood.to += ID.a2b ;

        this->push_back(youngeBlood);
    }

    return *this ;
}


#endif



