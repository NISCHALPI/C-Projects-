#include <iostream>
#include "../lib/bst/bst.h"

using namespace std;

int main(){
    BST<int> myBST;

  for (int i =0 ; i < 20 ; i++){
    myBST << i;
  }

  BST<int> myBST2;

  myBST2 = myBST;

  myBST2.postOrder();
  myBST.postOrder();

  return 0;

}
