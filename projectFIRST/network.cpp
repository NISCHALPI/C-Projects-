#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

#include "identifier.h"





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
        
        checkIdentier(temp);

        // Fix me 
        list << temp;
        
        
        parseTemp.clear();
       
    }

    inFILE.close();

}







int main(int argc, char** argv){

    if (argc == 1 || argc >3 ){

        cout << "Not Enough Args!";
    }

    SuperIdentifier list ;

    readData(argv[1], list);   
    
    Identifier* temp ;
    
    return 0;
}
