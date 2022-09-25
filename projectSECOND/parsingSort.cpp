#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Class to store unique // Imports Custom Lib automatically 
#include "include/pseudovector.h"


/////////////////////////////////////////Function Signature////////////////////////////////////
// Created to reuse code 
template <typename useType>
void printUnique( int argc , char** argv);






//////////////////////////////////////////// Main Function///////////////////////////////////
int main(int argc, char** argv){



// Command Line args Guard
if ( argc != 4 ){

    cout << "Not Enough Args! " << endl;
    exit(-1);
}


// Use function template for specific data type
if (argv[1][0] == 'i'){

printUnique<int>(argc, argv);

}
else if  (argv[1][0] == 's'){
printUnique<string>(argc, argv);

}




// Sucess
return 0;

}






////////////////////////////////////////////Function Implementation/////////////////////////////
template <typename useType>
void printUnique(int argc , char** argv){


// Vector Class Decleration
PseudoVector<useType> first;
PseudoVector<useType> second;
PseudoVector<useType> unique;

// Stream For Reading 
ifstream inFile1(argv[2]);
ifstream inFile2(argv[3]);


// Temp Variable
useType temp;


// Append to Vectors
while (!inFile1.fail())
    {
        inFile1 >> temp;
        first.push_back(temp);
    }
    
while (!inFile2.fail())
{
    inFile2 >> temp;
    second.push_back(temp);
}


//EMPTY GUARD
if(first.getSize() == 0 || second.getSize()==0){
    return ;
}

// Close Files
inFile1.close();
inFile2.close();


// When to use merge and threads
bool useMerge = typeid(useType) == typeid(int);
bool useThread = (__CPU__COUNT >= 6);



//Sort both array
first.sort(useMerge, useThread);
second.sort(useMerge , useThread);


bool usedFirst = true;

// Find Unique in small one 
if (second.getSize() > first.getSize()){
first.unique(unique);
}
else{
    usedFirst = false;
    second.unique(unique);
}



// Use unique to find intersecting
if (usedFirst){

// Loop and Find through second
for(int i =0 ; i < unique.getSize() ; i++ ){
    if (second.find(unique.at(i)) != -1){
        cout << unique.at(i) << endl;
        }
 }

}
else{

// Loop and Find throuch first
for(int i =0 ; i < unique.getSize() ; i++ ){
    if (first.find(unique.at(i)) != -1){
        cout << first.at(i) << endl;
        }
 }


}


return;

}