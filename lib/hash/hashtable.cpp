#include <iostream>
#include "primes.h"
#include "../list/list.h"

// Define rehashing capacity
#ifndef __HASH_CAPACITY__
#define __HASH_CAPACITY__ 50
#endif


// Uses Modulus Hash Function
// HashTables Class
template <typename Item>
class HashTable{

// Private vars 
private:

    // List of array  
    List<Item>* __array = nullptr;
     
    // Size of Table 
    int __size;


    // Capacity 
    int __capacity;

    //HashFunction pointer 
    int (*funcptr)(Item);

    // currentLoad 
    int __load;


// Public Section 
public:

    // Constrcter 
    HashTable(int (*funcptr)(Item)){

        // Assign Hash Function Ptr to user define hash function
        this->funcptr = funcptr;

        // Assign the min array size 
        __size = 0 ;

        // Assigns Capcity to the environment variable
        __capacity = __HASH_CAPACITY__;

        // Intitialize Array
        __array = new List<Item>[__capacity];

    }



    






};



