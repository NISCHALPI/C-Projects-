#ifndef __HASHTABLE__LIB__
#define __HASHTABLE__LIB__


//
// hashtable.h: HashTable Calss 
//
// Author:  Nischal Bhattarai
//     
//
// Completion Date: 10/22/2022
// 
// Features: No Data Size Needed, Auto Rehashable, Optimized Primes Numbers for Mapping 
//
 

// Required Inputs 
#include "primes.h"
#include "../list/list.h"



// Define rehashing capacity
#ifndef __HASH_CAPACITY__
#define __HASH_CAPACITY__ 53
#define __HASH_LIMIT__ 8 
#endif




// Chained HashTable Name Space 
namespace chainedHash {


// Node Class HashTable
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


/**
 * @brief Chained HashTable Class with Linked List Buckets 
 *        Automatic Rehash with prime numbers 
 *        
 * 
 * @tparam Pass a Hash Function to the constructer such that int func(object) 
 */
template <typename Item>
class HashTable{

// Private vars 
private:

    // List of array  
    __HashNode<Item>* __array = nullptr;
     
    // Int totalElement 
    int __element = 0;

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


        // Reset Vars 
        __size = 0 ;
        __maxBucketLoad = 0;
        __element = 0;

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

    // void clear | realloc array after use
    void __clear(){

        // Delets the array
        delete[] __array;

        // Assign the min array size 
        __size = 0 ;
        
        // Assigns Capcity to the environment variable
        __capacity = __HASH_CAPACITY__;
        
        // Max Bucket Load is Zero
        __maxBucketLoad = 0; 

        __element = 0;

    }



// Public Section 
public:

    // Constructer 
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

        __element = 0;


    }

    // Destructor
    ~HashTable(){
        __clear();
    }

    // Copy Constructer 
    HashTable(const HashTable& rhs){
        
        // Refrences same hash function 
        this->hashFunction = rhs.hashFunction;

        // Assign the min array size 
        __size = rhs.__size ;

        // Assigns Capcity to the environment variable
        __capacity = rhs.__capacity;

        // Intitialize Array
        __array = new __HashNode<Item>[__capacity];

        // Max Bucket Load is Zero
        __maxBucketLoad = rhs.__maxBucketLoad; 

        __element = rhs.__element;

        // Recopy Everything
        for(int i=0 ; i<__capacity; i++ ){
            this->__array[i] = rhs.__array[i];
        }

        }

    

    //Copy Assignment operator
   chainedHash::HashTable<Item>& operator=(const HashTable<Item>& rhs){

        // Self Copy GUard
        if(this == &rhs){
            return *this;
        }

        // Clear Hash Function 
        this->__clear();

        // Copy other data types
        // Refrences same hash function 
        this->hashFunction = rhs.hashFunction;

        // Assign the min array size 
        __size = rhs.__size ;

        // Assigns Capcity to the environment variable
        __capacity = rhs.__capacity;

        // Intitialize Array
        __array = new __HashNode<Item>[__capacity];

        // Max Bucket Load is Zero
        __maxBucketLoad = rhs.__maxBucketLoad; 

        __element = rhs.__element;

        for(int i=0 ; i<__capacity; i++ ){
            this->__array[i] = rhs.__array[i];
        }

        return *this;


   }
    
    /////////////////////////////////////////////////////////////SECTION: Getters/////////////////////////////////////////////////////////// 
    
    int getBucketSize() const {return __size;}
    
    int getCapacity() const {return __capacity;}
    
    int getMaxBucket() const {return __maxBucketLoad;}
    
    int getSize() const { return __element;}
    
    void printHash(std::ostream& inpStream = std::cout) const {
        
        for (int i = 0 ; i < __capacity; i++){
            if (!__array[i].isEmpty()){
                __array[i].__bucketList.print_head(inpStream);
            }
            
        }
    }

    
    //////////////////////////////////////////////////////////////SECTION: Setters/////////////////////////////////////////////////////////
    

    // Find method
    bool search(Item  data){
        int key = this->hashFunction(data) % __capacity;
        return __array[key].__bucketList.search(data);

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
        
        // Increment Size list 
        __element++;

        // Load of the List 
        double load = (__size / double(__capacity));

        // Rehasing Condition 
        if ((__maxBucketLoad > int(sqrt(__capacity) +1 )) && (load > 0.66)) {
            __rehash();
        }



    } 
    
    bool remove(Item data){

        // Index = key % capacity
        int index = hashFunction(data) & __capacity;

        try {
            
            bool isRemoved = __array[index].__bucketList.pop_value(data);
            
            // Reduce Size
            __element--;

            return (isRemoved)? true : false; 

        }
        catch (std::logic_error){
            return false;
        }

        return false;

    }

    void clear() {

        // Clear the array and do new alloc
        this->__clear();

        // New capacity alloc 
        __array = new __HashNode<Item>[__capacity];


    }

    //////////////////////////////////////////////////////////////SECTIONS: OVERLOADS////////////////////////////////////////////////////////
    
    // Hash OvearLoad 
    friend chainedHash::HashTable<Item>& operator<<(chainedHash::HashTable<Item>& refHash , Item valAdd){
        refHash.hash(valAdd);
        return refHash;
        }

    friend std::ostream& operator<<(std::ostream& out , const chainedHash::HashTable<Item>& refHash ){

            refHash.printHash(out);
            return out;
    }

};


};

#endif 