#include <iostream>
#include "primes.h"
#include "../list/list.h"






// Define rehashing capacity
#ifndef __HASH_CAPACITY__
#define __HASH_CAPACITY__ 47
#define __HASH_LIMIT__ 8
#endif



template <typename Item>
class __HashNode{

    private:        
        List<Item> __bucketList;
        int __key;


    public:
        
        bool isEmpty() { return (__bucketList.getSize() == 0) ? true : false ;}

        __HashNode<Item>& operator=(const __HashNode<Item>& src){
            
            if (this == &src){
                return *this;
            }
            
            
            this->__bucketList = src.__bucketList;
            this->__key = src.__key;

            return *this;
        }

        template <typename Ref>
        friend class HashTable ;
    
};





// Uses Modulus Hash Function
// HashTables Class
template <typename Item>
class HashTable{

// Private vars 
private:

    // List of array  
    __HashNode<Item>* __array = nullptr;
     
    // Size of Table 
    int __size;

    // Capacity 
    int __capacity;

    //HashFunction pointer 
    int (*hashFunction)(Item);

    // Max bucket Load 
    int __maxBucketLoad ;

    

//////////////////////////////////////////////////SECTION: PRIVATE HELPER FUNCTTION/////////////////////////////////////////////////////////////

    // Rehashing Fuction
    void __rehash() {

        // Previous capacity 
        int prevCap = __capacity;

        // Directly Rehashesh
        auto tempArray = __array;
        
        // New Prime Number Capacity
        __capacity = __getHigherPrime(__capacity, 2 * __capacity);


        // new Increased arrat
        __array = new __HashNode<Item>[__capacity];


        // Reset Size 
        __size = 0 ;
        __maxBucketLoad = 0;

        // Temp size var
        int size = 0;

        // Rehash
        for (int i = 0 ; i < prevCap ; i++){
            
            if (!tempArray[i].isEmpty()){
                
                size = tempArray[i].__bucketList.getSize();
                
                for (int j = 0 ; j < size; j ++){
                    hash(tempArray[i].__bucketList.pop_front());
                }

            }

        }

        // free previous array
        delete[] tempArray;


    }


// Public Section 
public:

    // Constrcter 
    HashTable(int (*funcptr)(Item)){

        // Assign Hash Function Ptr to user define hash function
        this->hashFunction = funcptr;

        // Assign the min array size 
        __size = 0 ;

        // Assigns Capcity to the environment variable
        __capacity = __HASH_CAPACITY__;

        // Intitialize Array
        __array = new __HashNode<Item>[__capacity];

        // Max Bucket Load is Zero
        __maxBucketLoad = 0; 


    }

    // Destructor
    ~HashTable(){
        delete[] __array;
    }

    //addItem
    
    void hash(Item data){

        // Converts data integer Key 
        int key = hashFunction(data);
        
        // Finds the index with respect to  array
        int index = key % __capacity;

        // Finds the bucket for the key
        if (__array[index].isEmpty()){
            __array[index].__key = key;
            __array[index].__bucketList.push_back(data);
            __size++;             //Increment new size
        }
        else {
            __array[index].__bucketList.push_back(data);
        }

        // Replace max 
        if (__array[index].__bucketList.getSize() > __maxBucketLoad){
            __maxBucketLoad = __array[index].__bucketList.getSize();
        }

        // Load of the List 
        double load = (__size / double(__capacity));

        // Rehasing Condition 
        if ((__maxBucketLoad > int(sqrt(__capacity) +1 )) && (load > 0.66)) {
            __rehash();
        }



    } 
    
    void print() const {
        
        for (int i = 0 ; i < __capacity; i++){
            if (!__array[i].isEmpty()){
                __array[i].__bucketList.print_head(std::cout);
            }
            
        }
    }

    // Getters 
    int getSize() const {return __size;}
    int getCapacity() const {return __capacity;}
    int getMaxBucket() const {return __maxBucketLoad;}

    // Find method
    bool search(Item  data){
        int key = this->hashFunction(data) % __capacity;
        return __array[key].__bucketList.search(data);

    }


};





int hashFunc(int a) {return a;}



int main(){

    HashTable<int> myHash(hashFunc);

    for(int i = 0 ; i < 10000 ; i++){
        myHash.hash(rand() % 1000);
    }

    std::cout << "Capacity = "<<  myHash.getCapacity() << std::endl;
    std::cout << "Size = "<<  myHash.getSize() << std::endl;
    std::cout << "Bucket Size = "<<  myHash.getMaxBucket() << std::endl;
    myHash.print();
    std::cout << std::boolalpha << myHash.search(22) << std::endl;

}
