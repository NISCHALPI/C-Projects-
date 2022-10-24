#ifndef __PROJECT_UTILS__
#define __PROJECT_UTILS__

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
using namespace std;

// Get Val
void getVal(istream &is, string &str) {
    char ch;
    string line;

    is >> ch;
    getline(is, line);

    str = ch + line;
}

// djb2 String Hash Function
uint64_t djb2(string str) {
    const char *ptr = str.c_str();
    uint64_t hash = 5381;
    int c;
    while ((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

// Valid Key Checker
bool isValidKey(const string &key) {
    string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };
    for (int i = 0; i < 8; i++) {
        if (key == validKeys[i]) {
            return true;
        }
    }
    return false;
}


// Parse Function 
void parse(string& str, vector<string>& readVect){

    

    istringstream strStm(str);

    string temp;

    for (int i = 0; i< 8 ; i++){
         getline(strStm, temp, '\t'); 
         readVect.push_back(temp);
         temp.clear();
     }

     strStm.clear();




}



// Person Class 
class Person{


public:
    string id;
    string firstName;
    string lastName;
    string email;
    string phone;
    string city;
    string state;
    string postalCode;

    // Hash Key 
    uint64_t key = 0;

    // Read Operator Overload
    friend Person& operator<<(Person& writeObj, vector<string>& dataList){
        
        // Assinment 
        writeObj.id = dataList.at(0);
        writeObj.firstName = dataList.at(1);
        writeObj.lastName = dataList.at(2);
        writeObj.email = dataList.at(3);
        writeObj.phone = dataList.at(4);
        writeObj.city = dataList.at(5);
        writeObj.state = dataList.at(6);
        writeObj.postalCode = dataList.at(7);

        // Clear the vector 
        dataList.clear();

        // Return the refrence to the data 
        return writeObj;

    
    }

    string getAttr(string name){
        
        // Key List 
        string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };

        // Check for attributes 
        if(name==validKeys[0]) return id;
        if(name==validKeys[1]) return firstName;
        if(name==validKeys[2]) return lastName ;
        if(name==validKeys[3]) return email ;
        if(name==validKeys[4]) return phone ;
        if(name==validKeys[5]) return city ;
        if(name==validKeys[6]) return state ;
        if(name==validKeys[7]) return postalCode ;

        //Throw error if not found 
        throw std::logic_error("Attribute not found");
        
        // pseudo return | wont reach here 
        return string("None");

    }

    void print(){

        cout << id << "," << firstName << "," << lastName << "," << email << "," << phone << "," << city << "," << state << "," << postalCode << endl;

    }


};



class HashTable{

    // Private Elements
    private:

        // Size of table  
        int __size = 0;
         
        // Hash Function 
        uint64_t (*hashFunc)(string obj)  = nullptr;

        // Hash list 
        list<Person>* __hashArray;

        // Attr to use 
        string hashAttr;
    
    public:

        // Constructer 
        HashTable(uint64_t (*funcptr)(string obj), int size, string hashAttr){

            //Assing the funcptr
            this->hashFunc = funcptr;

            // Allocate the size of the hashTable 
            this->__size =size;

            // Allocate new memort
            __hashArray = new list<Person>[size];

            // Hash attr 
            this->hashAttr = hashAttr; 
        }

        // Destructer 
        ~HashTable(){

            // delete hashList
            delete[] __hashArray;
        }
    
        // Hash method 
        void hash(Person refPerson){

            // Extract key 
            uint64_t key = hashFunc(refPerson.getAttr(hashAttr)); 
            
            // assign key to each person 
            refPerson.key = key;

            // Guard
            if (__size==0){ throw logic_error("Size is 0! Mod operater returns error");}
            
            // index mapped 
            int index;

            // Quadratic Probing 
            for(int i=0; i<__size; i++ ){
                
                // new Key Update 
                index = (key + i + i *i) % __size;
                
                // If Empty or Keys are Equal, insert or probe
                if (__hashArray[index].size() == 0 || __hashArray[index].front().key == refPerson.key){
                    
                    __hashArray[index].push_back(refPerson);

                    break;
                }


            }





        }
        
        // Print method 
        void print() {

            for(int i =0 ; i < __size ; i++){

                // If not empty 
                if (!(__hashArray[i].size() ==0)){

                    // Print in format 
                    cout <<  i << ": " << __hashArray[i].front().getAttr(hashAttr) << " (" << __hashArray[i].size() << ")," << endl; 
                }

            }
            
        }

        void lookup( string lookupKey) {

            // Hash key to index 
            uint64_t key = hashFunc(lookupKey);


            // Look index 
            int lookIndex = 0;

            // Find and Print 
            for (int i =0 ; i<__size ; i++){

                // look up Key 
                lookIndex = (key + i + i*i) % __size;

                


                if (__hashArray[lookIndex].size() == 0){
                    break;
                }

                if ( __hashArray[lookIndex].front().key ==  key){

                    cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;

                    for (auto elem : __hashArray[lookIndex]){
                        elem.print();
                    }

                    // Exit after Print
                    return;
                }


            }

            //If full
            cout << "No results" << endl;

        }

};




#endif


