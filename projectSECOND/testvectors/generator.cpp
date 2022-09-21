#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <random>

const int __MAX_WORD = 90000000;
int _MAX_TESTVECTOR_ONE = 200000;
int _MAX_TESTVECTOR_TWO = 200000;

using namespace std;

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

string random;

int count = 0;

while (count < __MAX_WORD){
    
    hold.push_back( random_string( (rand() % 15 + 3)));

    count++;
}

ofstream outFile("testvector1.txt");

count = 0 ;

while (count <_MAX_TESTVECTOR_ONE){

outFile <<  endl << hold.at( rand() % (hold.size()) )<< endl;

count++;
}


ofstream outFile2("testvector2.txt");

count = 0 ;

while (count <_MAX_TESTVECTOR_TWO){

outFile2 << " " << hold.at( rand() % (hold.size()) )  << endl;

count++;
}








    return 0;
}
