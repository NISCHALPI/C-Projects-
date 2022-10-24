#include "include/utilities.h"

using namespace std;




int main(int argc, char **argv) {
    

    // Pre Recs 

    if (argc != 4) {
        cout << "Usage: ./a.out filename.txt table_size key" << endl;
        return 1;
    }

    string filename = argv[1];
    int tableSize = stoi(argv[2]);
    string key = argv[3];


    ifstream file(filename);
    if (!file) {
        cout << "Unable to open " << filename << endl;
        return 2;
    }

    if (!isValidKey(key)) {
        cout << "Invalid key: " << key << endl;
        return 3;
    }

    // Temp Vector 
    vector<string> readVect;

    // Temp String 
    string tempString;

    // Consume Header
    getline(file , tempString);

    // Person item 
    Person tempPerson;

    // HashTable 
    HashTable  hashTable(djb2, tableSize, key);
    
    while (true){

        // Clears Each time 
        tempString.clear();
        readVect.clear();

        // End of file break
        if (!getline(file, tempString)){
            break;
        }

        // Parse String 
        parse(tempString , readVect);

        // Read Data
        tempPerson << readVect ;
        
        // Hash into a table 
        hashTable.hash(tempPerson);

    }

    // Hashing finished Now do the for loop for user input 
    cout << "Commands:" << endl << "\tprint" << endl << "\tlookup <key>" << endl << "\tquit" << endl;
    string cmd, val;
    while (1) {
        cout << endl << "Enter a command:" << endl;
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "print") {
            hashTable.print();
        }
        else if (cmd == "lookup") {
            getVal(cin, val);
            // lookup code here
            hashTable.lookup(val);
        }
        else {
            getline(cin, val);
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
