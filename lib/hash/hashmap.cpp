#include "hashtable.h"


template <typename keyType , typename valType>
class __Node{

public:
    keyType key;
    valType value;

    bool operator==(__Node<keyType , valType>& ref){
        return key==ref.key;
    }
    int func(int (*hashFunc)(keyType)){
        return hashFunc(key);
    }

};


template <typename keyType , typename valType>
class HashMap{

    

    private:
        

        // Func Ptr | key to integer 
        int (*hashFunc)(keyType);


        // Hash Table 
        chainedHash::HashTable<__Node<keyType, valType>> __hashTable();

        

    public:

        HashMap(int (*hashFunc)(keyType)){

            this->hashFunc = hashFunc;

        }

        void hash(keyType key, valType value){

            __hashTable << __Node<keyType , valType>(key , value);

        }

        valType& operator[](keyType key){
            
            return valType();
            
        }

       






};


int func(char c ){return int(c);}

int main(){


    HashMap<char, int > map(func) ;
    map.hash('c',1);
}


