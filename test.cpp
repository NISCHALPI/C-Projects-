#include <iostream>
#include "lib/bst/bst.h"


int main(){

    BST<int> myBst;

    for (int i =0 ; i < 100 ; i++){
        myBst << i ;
    }

    myBst.levelOrder();

    return 0 ;

}