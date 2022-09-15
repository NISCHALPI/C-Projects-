#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <random>

using namespace std;

const int _MAX_BANDWIDTH = 10000 ;
const int _MAX_TESTVECTOR = 100000;

void readData(ifstream& inputStream, vector<string>& identifierName){

string temp;

getline(inputStream , temp) ;

while(true){

if (temp.size() == 0) break;

identifierName.push_back(temp);

getline(inputStream, temp);
}

inputStream.close();

}


int getBandwidth(){

    return ( rand() % (_MAX_BANDWIDTH + 1 ) ) ;
}


int getindex( int size){

    return (rand() % size);
}


void writeData(vector<string>& identifierName){

    const int _UNIQUE_SIZE_ = identifierName.size();

    srand(time(NULL));

    ofstream outFS;

    outFS.open("testvector.txt");

    string temp;

    string temp2;

    for (int i = 0; i < _MAX_TESTVECTOR ; i++){
        temp = identifierName.at(getindex(_UNIQUE_SIZE_));
        
        outFS << temp << " " ;

        temp2 = identifierName.at(getindex(_UNIQUE_SIZE_));

        while(true){
            if (temp != temp2){
                outFS << temp2 << " " << getBandwidth() << endl;
                break; 
            }
            temp2 = identifierName.at(getindex(_UNIQUE_SIZE_));
        }


    }
    
   
    outFS.close();

}

std::string random_string(std::string::size_type length)
{
    static auto& chrs = "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    thread_local static std::mt19937 rg{std::random_device{}()};
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

    std::string s;

    s.reserve(length);

    while(length--)
        s += chrs[pick(rg)];

    return s;
}


void randomIdentifier(){
    
    ofstream outFS;

    outFS.open("random_string.txt");

    for (int i=0; i<(_MAX_TESTVECTOR/10); i++){

        outFS << random_string(10) << endl;
    }

    outFS.close();

}

int main(){


vector<string> identifierName;

randomIdentifier();


ifstream inFS("random_string.txt");

readData(inFS, identifierName);

writeData(identifierName);


return 0 ;
}
