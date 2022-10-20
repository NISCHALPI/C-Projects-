#ifndef __PRIMES__LIB__
#define __PRIMES__LIB__

#include <iostream>
#include <cmath>


// O(sqrt(n)) algorithm 
 bool __isPrime(int a){

    // Guard
    if (  a < 1){ throw std::logic_error("Primes are only defined for integers greater than 0");}

    // If 1 or 2 
    if ( a <= 2) {return true;}

    // Factors are seen in pairs :-  a*b = n | a can run max upto sqrt(n)
    // Checking for factors upto sqrt of n, implicitly checks the higher factors
    for (int i = 2 ; i < int(sqrt(a) + 1) ; i++){
        if ( a % i == 0){return false;}
    }

    //Return true if not divisible 
    return true ;

 }


// Gets a higher prime than current number 
int __getHigherPrime(int num){
    
    // temp val
    int initialVal = num;

    //increament first
    num++ ;
    
    while (!__isPrime(num)){
        num++;
    }

    return num;
    
}   

int __getHigherPrime(int num, int minSpacing){
    return __getHigherPrime(minSpacing + num);
}


#endif