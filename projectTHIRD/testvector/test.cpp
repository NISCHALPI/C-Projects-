#include <iostream>
#include <iomanip>
#include "../header/p3.h"

using namespace std;

void checkDestrectur(ContactList test){

    test.getCount();
}



int main (){

    ContactList testList;

    // Test add
    testList.addContact("Tony", "Stark");
    testList.addContactOrdered("Steve", "Rodgers");
    testList.addContactOrdered("Peter" ,"Parker");
    testList.addContactOrdered("Natasha" ,"Romanoff");
    testList.addContactOrdered("Wanda","Maximoff");
    testList.addInfoOrdered("Tony" ,"Stark" , "alias" ,"IronMan");
    testList.addInfoOrdered("Tony" ,"Stark" , "color" ,"red-and-gold");
    testList.addInfoOrdered("Peter" ,"Parker" , "alias" ,"Spider-Man");
    testList.addInfoOrdered("Peter" ,"Parker" , "color" ,"red-and-blue");
    testList.addInfoOrdered("Natasha" ,"Romanoff" , "birthday" ,"December-3-1984");
    testList.addInfoOrdered("Natasha","Romanoff" , "email" ,"black.widow@avengers.com");
    testList.addInfoOrdered("Natasha" ,"Romanoff" , "email" ,"BlackWidow");


    
    cout << testList.getCount() << endl;
    testList.print(cout);
}
