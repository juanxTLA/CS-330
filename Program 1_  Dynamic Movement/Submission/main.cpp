#include "character.cpp"
#include <fstream>
#include <iostream>

#define PI  3.1416

using namespace std;

int main(){
    ofstream outFile;
    outFile.open("test.txt");

    //Create continue character
    Character cont = Character(2601, {0,0}, {0,0}, {0,0}, 0, CONTINUE, false, -1);
    //create flee character

    for(double i = 0; i < 50; i += 0.5){
        string info = cont.printInfo();
        outFile << i << "," << info << endl;
    }

    return 0;

}