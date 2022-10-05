#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Info::Info() {
    this->name = "No Name Set";
    this->value = "No Value Set";
    this->next = nullptr;
}

Info::Info(std::string name, std::string value, Info *next) {
    this->name = name;
    this->value = value;
    this->next = next;
}

Contact::Contact() {
    this->first = "No First Set";
    this->last = "No Last Set";
    this->next = nullptr;
    this->headInfoList = nullptr;
}

Contact::Contact(std::string first, std::string last, Contact *next) {
    this->first = first;
    this->last = last;
    this->next = next;
    this->headInfoList = nullptr;
}

ContactList::ContactList() {
    this->headContactList = nullptr;
    this->count = 0;
}

int ContactList::getCount() {
    return this->count;
}





// Helper Function | Contact Method | Print 
void Contact::print( std::ostream &os) const {

    // Out the name in givern format : Contact Name: first last /n
    os << "Contact Name: " << this->first << " " << this->last << endl;

    // Print Fields Appropritately
    // Loops Correctly 
    
    for(Info* currInfo = headInfoList; currInfo!=nullptr; currInfo = currInfo->next){

        // Don't Print Last newline character
        os << "    " << currInfo->name << " | " <<  currInfo->value << endl;

    }

return;

}


// Helper Function} | Contact List Method | Search 
Contact*  ContactList::searchContact(std::string first, std::string last){
    
    // Loops over all contact linked list
    for(Contact* currContact = headContactList; currContact!=nullptr; currContact = currContact->next){
        if(currContact->first == first && currContact->last == last){
            return currContact;
        }
    }
    return nullptr;
}


// print the specified contact and its information
// 1. return false and print nothing if the contact is not in the list
// 2. otherwise return true and print the contact
bool ContactList::printContact(std::ostream &os, std::string first, std::string last) {
    
    //Declare Temp Variable for clarity
    Contact* myContact;

    //Search for the contact | returns pointer to the contact
    myContact = this->searchContact(first, last);

    // If not null ptr , print and return found 
    if(myContact != nullptr){
        myContact->print(os);
        return true;
    }
    
    //return false if not found
    return false;
}


// print all contacts and their information
// print nothing if the list is empty
void ContactList::print(std::ostream &os) {

// Loop and print regardless
for(Contact* currContact = headContactList; currContact!=nullptr; currContact = currContact->next){
        currContact->print(os);
    }

}


// add a contact to the back of the list
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the back of the list
// - do not forget to update count
bool ContactList::addContact(std::string first, std::string last) {
    
    
    // If head is empty
    if(headContactList == nullptr){

        headContactList = new Contact(first, last, nullptr);
        count++;
        
        return true;

    }



    // If not there
    if (searchContact(first, last) == nullptr){

        Contact* newContact = new Contact(first , last, nullptr);

        for(Contact* currContact = headContactList; currContact!=nullptr; currContact = currContact->next){
            
            if(currContact->next == nullptr){
                //Insert a node using static function 
                insertNode(currContact, newContact);
                break;
            }

        }

        count++;
        return true;
    }
    
    // If already there, do nothing
    return false; 
    
    
    
}



// Helper Function | Contct Method | search Info
Info* Contact::searchInfo(std::string infoName){

 // Loops over all contact linked list
    for(Info* currInfo = headInfoList; currInfo!=nullptr; currInfo = currInfo->next){
        
        //if name equals then return the pointer to Node 
        if(currInfo->name == infoName){
            return currInfo;
        }

    }

    return nullptr;
}







// add info to the back of a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the back of the contact's list and return true
bool ContactList::addInfo(std::string first, std::string last, std::string infoName, std::string infoVal) {
    
    Contact* currContact = searchContact(first, last);
    
    // If found, proceed
    if(currContact != nullptr){

        // if head is empty
        if (currContact->headInfoList == nullptr){
           currContact->headInfoList = new Info(infoName, infoVal);
        }



        Info* newInfo = currContact->searchInfo(infoName);

        // if not found 
        if(newInfo == nullptr){
            
            newInfo = new Info(infoName, infoVal);
            
            // Iterate and add
            for(Info* currInfo = currContact->headInfoList ; currInfo != nullptr ; currInfo= currInfo->next){

                if (currInfo->next == nullptr){
                insertNode(currInfo , newInfo);
                break;
                }

                }
        
          
        }
        else{
            newInfo->value = infoVal;
        }

        // Return true if found and added
        //  No counter to update 
        return true;
    }
    
    // return fase if not found
    return false;
    
}


//////////////////////////////////////////////////COMPARE FUNCTON/////////////////////////////

enum class CompareType {LastFirst, Equality , InfoName};

bool compareContact(Contact* compareFirst , Contact* compareSecond, CompareType type){
    switch(type){
        
        case CompareType::LastFirst:
            if (compareFirst->last > compareSecond->last) return true;
            if (compareFirst->last < compareSecond->last) return false;
            if (compareFirst->first > compareSecond->first) return true;
            return false;
        
        case CompareType::Equality:
            return ((compareFirst->first == compareSecond->first) && (compareFirst->first == compareSecond->first));
        
        default:
            return false;
    }
}

bool compareInfo(Info* compareFirst , Info* compareSecond, CompareType type){
switch(type){
        
        case CompareType::InfoName:
            if(compareFirst->name > compareSecond->name) return true;
            return false;

        
        case CompareType::Equality:
            return (compareFirst->name == compareSecond->name) ;
        
        default:
            return false;
    }
}




//////////////////////////////////////////////////////////////////////////////////////////////

// add a contact to the list in ascending order by last name
//     if last names are equal, then order by first name ascending
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the list
// - do not forget to update count
// - compare strings with the built-in comparison operators: <, >, ==, etc.
// - a compare method/function is recommended
bool ContactList::addContactOrdered(std::string first, std::string last) {
    
    if(searchContact(first, last) == nullptr ){

        // If head is itself empty
        if (headContactList == nullptr){
            addContact(first , last);
            return true;
        }
        
        // To add Node
        Contact* toAdd = new Contact(first, last);

        // Compare with first element | add front 
        if (compareContact(headContactList , toAdd, CompareType::LastFirst)){
            
            toAdd->next = headContactList;
            headContactList = toAdd;
            count++;
            return true;
        } 

        Contact* now = headContactList;
        Contact* infont = headContactList->next;

        bool isAdded = false;

        //Add until found
        while(infont != nullptr){

            //insersion Case 
            if (compareContact(infont, toAdd, CompareType::LastFirst)){
               insertNode(now, toAdd);
               isAdded =true; 
               break;
            }

            // Increaments 
            now = now->next;
            infont = infont->next;
        }

        //if Highest
        if (!isAdded){
            insertNode(now , toAdd);
        }

        count++;
        return true;
        
    }

    return false;

}






// add info to a contact's info list in ascending order by infoName
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the contact's list and return true
bool ContactList::addInfoOrdered(std::string first, std::string last, std::string infoName, std::string infoVal) {
    
    Contact* currContact = searchContact(first, last);
    
    // If found, proceed
    if(currContact != nullptr){

        
        // if head is empty
        if (currContact->headInfoList == nullptr){
           addInfo(first, last , infoName , infoVal);
           return true;
        }

        // if already there, update info 
        if(currContact->searchInfo(infoName)){
            addInfo(first, last , infoName , infoVal);
            return true;
        }

        Info* toAdd = new Info(infoName, infoVal);

        // Compate with first 
        if(compareInfo(currContact->headInfoList, toAdd, CompareType::InfoName)){
            toAdd->next = currContact->headInfoList;
            currContact->headInfoList = toAdd;
            return true;
        }

        Info* now = currContact->headInfoList;
        Info* infront = currContact->headInfoList->next;

        bool isAdded = false;

        while(infront != nullptr){
            if(compareInfo(infront, toAdd, CompareType::InfoName)){
                insertNode(now , toAdd);
                isAdded = true;
            }
            now = now->next;
            infront = infront->next;
        }

        if (!isAdded){
            addInfo(first, last , infoName , infoVal);
        }


        // Return true if found and added
        //  No counter to update 
        return true;
    }
    
    // return fase if not found
    return false;
    
}









///// DONE UPTO HERE///////////////////////

// remove the contact and its info from the list
// 1. return false and do nothing if the contact is not in the list
// 2. otherwise return true and remove the contact and its info
// - do not forget to update count
bool ContactList::removeContact(std::string first, std::string last) {
    
    bool isRemoved = false;
    
    // Null Guard
    if (headContactList == nullptr){
        return isRemoved;
    }

    // temp vars
    Contact* beforeItem = headContactList;
    Contact* currItem = headContactList->next;

    // Check First
    if(beforeItem->first == first && beforeItem->last == last){
        // Switch head
        headContactList = currItem;

        //Deleted
        beforeItem->clear();
        delete beforeItem;

        count--;
        return true;
    }
    
    // Check Else 
    while(currItem != nullptr){

        if(currItem->first == first && currItem->last == last){
            
            // Clear the Info List 
            currItem->clear();
            
            //Removes Node
            removeNode(beforeItem, currItem);

            isRemoved = true;
            count--;
            break;
        }

        currItem =currItem->next;
        beforeItem =beforeItem->next;
    }

    return isRemoved;
}

// remove the info from a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. return false and do nothing if the info is not in the contact's info list
// 3. otherwise return true and remove the info from the contact's list
bool ContactList::removeInfo(std::string first, std::string last, std::string infoName) {
    
    Contact* currContact = searchContact(first, last);

    // If contact not in the list
    if (currContact == nullptr){
        return false;
    }

    // Search Info not in Info list
    if (currContact->searchInfo(infoName) == nullptr){
        return false;
    }

    Info* currInfo = currContact->headInfoList;
    Info* nextInfo = currContact->headInfoList->next;


    // Compare first one -- guranteed to exist
    if (currInfo->name == infoName){
        currContact->headInfoList = nextInfo;
        delete currInfo;
        return true;
    }

    // Loops to find a new one
    while(nextInfo !=nullptr){

        if(nextInfo->name == infoName){
            removeNode(currInfo, nextInfo);
            return true;
        }
        currInfo = currInfo->next;
        nextInfo = nextInfo->next;
    }

    return false;


}

    

// destroy the list by removing all contacts and their infos
ContactList::~ContactList() {
    
    // Call clear method of Contact List
    clear();
   
}

// deep copy the source list
// - do not forget to update count
ContactList::ContactList(const ContactList &src) {

    // Default Constructer
    this->headContactList = nullptr;
    this->count = 0;


    Contact* srcHead = src.headContactList;
    Info* srcInfo;


    while(srcHead != nullptr){
        
        // Add Contact from srcHead
        addContact(srcHead->first ,srcHead->last);

        // Increment Source Info
        srcInfo = srcHead->headInfoList;
        
        
        // Copy Source 
        while(srcInfo != nullptr){
            addInfo(srcHead->first, srcHead->last, srcInfo->name ,srcInfo->value);
            
            // Info Increment 
            srcInfo = srcInfo->next;
        }

        // Head Increment
        srcHead = srcHead->next;
    }
}


// remove all contacts and their info then deep copy the source list
// - do not forget to update count
const ContactList &ContactList::operator=(const ContactList &src) {
    
    // Self Assignment 
    if (this == &src) {
        return *this;
    }
    
   clear();

    Contact* srcHead = src.headContactList;
    Info* srcInfo;


    while(srcHead != nullptr){
        
        // Add Contact from srcHead
        addContact(srcHead->first ,srcHead->last);

        // Increment Source Info
        srcInfo = srcHead->headInfoList;
        
        
        // Copy Source 
        while(srcInfo != nullptr){
            addInfo(srcHead->first, srcHead->last, srcInfo->name ,srcInfo->value);
            
            // Info Increment 
            srcInfo = srcInfo->next;
        }

        // Head Increment
        srcHead = srcHead->next;
    }

    return *this;
}
