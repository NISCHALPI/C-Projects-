#include <iostream>
#include "headers/identifier.h"
#include "headers/writer.h"

int main(int argc, char** argv){
    if (argc !=3){

        cout << "Not Enough Args!" << endl;   
        exit (EXIT_FAILURE) ;


    }
    
    SuperIdentifier list ;
    
    readData(argv[1], list);   
    
    writeData(argv[2], list) ;
    
    return 0;
}
