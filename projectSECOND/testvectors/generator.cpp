#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <random>


// __MAX_RANDOM WORD TO CHOOSE | POOL OF WORD
const int __MAX_WORD = 9000000;

// MAX TESTVECTOR1.txt 
int _MAX_TESTVECTOR_ONE = 200000;

// MAX TESTVECTOR2.txt
int _MAX_TESTVECTOR_TWO = 200000;



using namespace std;

// RANDOM STRING GENERATOR | ARGUMENT : LENGTH OF STRING 
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


int main(){





vector<string> hold;


// Random chars in bet'n string
char __random_chars[3] = {'\n', '\t' , ' '};


string random;

int count = 0;

while (count < __MAX_WORD){
    
    hold.push_back( random_string( (rand() % 15 + 3)));

    count++;
}


ofstream outFile("testvector1.txt");

count = 0 ;

while (count <_MAX_TESTVECTOR_ONE){

outFile << __random_chars[rand() % 3]<< hold.at( rand() % (hold.size()) )<< __random_chars[rand() % 3] << endl;

count++;
}


ofstream outFile2("testvector2.txt");

count = 0 ;

while (count <_MAX_TESTVECTOR_TWO){

outFile2 << __random_chars[rand() % 3] << hold.at( rand() % (hold.size()) ) <<__random_chars[rand() % 3]  << endl;

count++;
}








    return 0;
}
