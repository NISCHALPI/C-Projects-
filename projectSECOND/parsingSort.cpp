#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Class to store unique // Imports Custom Lib automatically 
#include "include/pseudovector.h"



int main(int argc, char** argv){

if ( argc != 4 ){

    cout << "Not Enough Args! " << endl;
    exit(-1);
}



if (argv[1][0] == 'i'){
    PseudoVector<int> first;
    PseudoVector<int> second;

    PseudoVector<int> unique;

    ifstream inFile1(argv[2]);
    ifstream inFile2(argv[3]);


    int temp;


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
        return 0;
    }

    inFile1.close();
    inFile2.close();
    

    first.sort(true);
    second.sort(true);

    
    first.unique(unique);

    for(int i =0 ; i < unique.getSize() ; i++ ){
        if (second.find(unique.at(i)) != -1){
            cout << unique.at(i) << endl;
        }
    }
    
}
else if (argv[1][0] == 's'){
    //Declare 
    PseudoVector<string> first;
    PseudoVector<string> second;

    PseudoVector<string> unique;

    ifstream inFile1(argv[2]);
    ifstream inFile2(argv[3]);


    string temp;

    // Read
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
    //Close file

    inFile1.close();
    inFile2.close();

    //EMPTY GUARD
    if(first.getSize() == 0 || second.getSize()==0){
        return 0;
    }

    //Sort
    first.sort(true);
    second.sort(true );

    first.unique(unique);

    //Uniques
    for(int i =0 ; i < unique.getSize() ; i++ ){
        if (second.find(unique.at(i)) != -1){
            cout << unique.at(i) << endl;
        }
    }
    
}




return 0;
}
