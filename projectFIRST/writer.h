#ifndef _WRITER_H
#define _WRINTER_H


#include "identifier.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <iomanip>


bool checkIdentier(tempID& temp){
    
    for (int i =0 ; i< temp.name1.size(); i++){
        if(!(isalnum(temp.name1.at(i)))){
            return false ;
        }
        else if ((isalpha(temp.name1.at(i))))  {
            temp.name1.at(i) =toupper(temp.name1.at(i));
        }
    }
    for (int i =0 ; i< temp.name2.size(); i++){
        if(!(isalnum(temp.name2.at(i)))){
            return false ;
        }
        else if ((isalpha(temp.name2.at(i))))  {
            temp.name2.at(i) =toupper(temp.name2.at(i));
        }
    }

    
    return true; 

}


void readData(string filename, SuperIdentifier& list){

    ifstream inFILE(filename);
    stringstream parseTemp;
    tempID temp;
    string tempString;

    if (!inFILE.is_open()){
        cout << "Couldn't open the file!";
        exit (EXIT_FAILURE); 
    }
    
   
    while (true){
        getline(inFILE, tempString);

        if (inFILE.fail()){
            break;
        }

        

        parseTemp.str(tempString);

        try {
            parseTemp >> temp.name1 ;
            parseTemp >> temp.name2;
            parseTemp >> temp.a2b;
        }
        catch (...){
            cout << "Reading faliure!";
            exit (EXIT_FAILURE);
        }   
        
        if (checkIdentier(temp) ){
        list << temp;
        }

        
        
        parseTemp.clear();
       
    }

    inFILE.close();

}


void writeData(string filename , SuperIdentifier& list){

    ofstream outFS;
    outFS.open(filename);

    if (!outFS.is_open()) {

        cout << "Cannot Write!" << endl ;
        exit(-1);
    }

    for (int i = 0; i < list.size; i++){
    
    outFS << list.at(i)->name << endl;

    list.at(i)->CheckLeaf() ;

    }
    
    outFS << endl ; 

   
    for (int i = 0; i < list.size; i++){
    
    if ( !list.at(i)->isLeaf ){
        outFS << fixed << setprecision(2);
        outFS << list.at(i)->name << " " << list.at(i)->from << " " << list.at(i)->to << " " << list.at(i)->GetRatio() << endl;
    }
    }

    outFS.close();

}






#endif