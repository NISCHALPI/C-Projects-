#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <random>




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



int main(int argc , char** argv){


if (argc != 5){

cout << "Usage is follows:" <<endl <<  endl ;
cout << "If you want to generate two file with 1000 words with few intersecting words, use following syntax: " << endl << endl;
cout << "./a.exe s 10000 1000 1000" << endl << endl;
cout << "s stands for string, use i for int" << endl ;
cout << "first 10,000 is for pool of words to randomly choose form" << endl;
cout << "Following 1000 is the amount of items in each file" << endl << endl;
cout << "Files will be named test1.txt and test2.txt" << endl;

exit (-1);

}


// Dimensions 
int __MAX_WORD = atoi(argv[2]);

int _MAX_TESTVECTOR_ONE = atoi(argv[3]);

int _MAX_TESTVECTOR_TWO = atoi(argv[4]);





// Random chars in bet'n string
char __random_chars[3] = {'\n', '\t' , ' '};



// Out Streams 
ofstream outFile("test1.txt");
ofstream outFile2("test2.txt");



if (argv[1][0] == 'i'){

    for(int i =0; i <_MAX_TESTVECTOR_ONE; i++ ){

        outFile << __random_chars[rand() % 3] << rand() % __MAX_WORD << __random_chars[rand() % 3] ; 

    }

    for(int i =0; i <_MAX_TESTVECTOR_TWO; i++ ){

        outFile2 << __random_chars[rand() % 3] << rand() % __MAX_WORD << __random_chars[rand() % 3] ; 

    }

}

else {
    // Pool Vector
    vector<string> hold;

    for(int i =0; i <__MAX_WORD; i++ ){
        hold.push_back(random_string(rand() % 15));
       
    }
    

    for(int i =0; i <_MAX_TESTVECTOR_ONE; i++ ){

        outFile << __random_chars[rand() % 3] <<  hold.at(rand() % __MAX_WORD)<< __random_chars[rand() % 3] << endl ; 

    }

    for(int i =0; i <_MAX_TESTVECTOR_TWO; i++ ){

        outFile2 << __random_chars[rand() % 3] <<  hold.at(rand() % __MAX_WORD) << __random_chars[rand() % 3] << endl ; 

    }




}
outFile.close();
outFile2.close();




    return 0;
}
