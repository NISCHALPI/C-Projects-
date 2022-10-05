#ifndef _P3_H_
#define _P3_H_

#include <iostream>
#include <string>


// Static Function to insert Node | available to any class
template<typename Item>
static void insertNode(Item* before, Item* insersion){

// Temporarly Store current after Node address 
Item* afterAddress = before->next;

//Overwrite before 
before->next = insersion;

//Rewrite Insersion
insersion->next = afterAddress;

return;

}


// Static Function to removeNode | available to any class
template<typename Item>
static void removeNode(Item* itemBefore , Item* itemToRemove){

    //Null Guard
    if(itemToRemove != nullptr){
        itemBefore->next = itemToRemove->next;
        delete itemToRemove;
    }



}





class Info {
public:
    std::string name;
    std::string value;
    Info *next;

    Info();
    Info(std::string name, std::string value, Info *next = nullptr);
};

class Contact {
public:
    std::string first;
    std::string last;
    Contact *next;
    Info *headInfoList;
    
    Contact();
    Contact(std::string first, std::string last, Contact *next = nullptr);
    
    //ADDED HELPER FUNCTIOM
    void print(std::ostream& os) const;
    
    //Info search in contact
    Info* searchInfo(std::string infoName);

    // Avoid mem leak | Clear method
    void clear(){

        Info* temp ;
        
        while(headInfoList != nullptr){
            temp = headInfoList;
            headInfoList = headInfoList->next;
            free(temp);    
        }

    }

};

class ContactList {
private:
    Contact *headContactList;
    int count;
public:
    ContactList();

    int getCount();
    
    bool printContact(std::ostream &os, std::string first, std::string last);
    void print(std::ostream &os);

    bool addContact(std::string first, std::string last);
    bool addInfo(std::string first, std::string last, std::string infoName, std::string infoVal);

    bool addContactOrdered(std::string first, std::string last);
    bool addInfoOrdered(std::string first, std::string last, std::string infoName, std::string infoVal);
    
    bool removeContact(std::string first, std::string last);
    bool removeInfo(std::string first, std::string last, std::string infoName);

    ~ContactList();
    ContactList(const ContactList &src);
    const ContactList &operator=(const ContactList &src);

    // HELPER FUNCTION ADDED 
    Contact* searchContact(std::string first, std::string last);
    
    // Clear Function
    void clear(){
        Contact* temp;

        while(headContactList !=nullptr){
            
            
            //Use temp
            temp = headContactList;
        
            //Switch head 
            headContactList = headContactList->next;
        
            //Call remove contact
            removeContact(temp->first , temp->last);
        }

        // Count is zero
        count = 0;

    }

    };

#endif
