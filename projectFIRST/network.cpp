#include <iostream>
#include "identifier.h"
#include "writer.h"





int main(int argc, char** argv){

    if (argc !=3){

        cout << "Not Enough Args!";
        
        exit(-1) ;

    }

    SuperIdentifier list ;

    readData(argv[1], list);   
    
    writeData(argv[2], list) ;


    
    
    return 0;
}
