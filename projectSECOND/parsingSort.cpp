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
    PseudoVector<string> first;
    PseudoVector<string> second;

    PseudoVector<string> unique;

    ifstream inFile1(argv[2]);
    ifstream inFile2(argv[3]);


    string temp;


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

    first.sort(false);
    second.sort(false);

    first.unique(unique);

    for(int i =0 ; i < unique.getSize() ; i++ ){
        if (second.find(unique.at(i)) != -1){
            cout << unique.at(i) << endl;
        }
    }
    
}




return 0;
}