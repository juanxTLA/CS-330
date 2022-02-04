#include "character.cpp"
#include "dynamic.cpp"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>


#define PI  3.1416

using namespace std;

int main(){
    ofstream outFile;
    outFile.open("test.txt");
    vector<Character> record;

    //Create continue character
    Character cont = Character(2601, {0,0}, {0,0}, {0,0}, 0, CONTINUE, false, NULL, 0,0);
    //create seek character
    Character seek = Character(2603, {2,7}, {-50,40}, {0,0}, PI/4, SEEK, false, &cont, 2, 8);

    record.push_back(cont);
    record.push_back(seek);

    //record[cont.getId()] = cont;
    //record[seek.getId()] = seek;
    Dynamic movement;

    double time = 0;
    double deltaTime = 0.5;
    double stopTime = 50;

    string info;

    while(time < stopTime){
        time += deltaTime;
        for(int i = 0; i < record.size(); i++){
            switch(record[i].getSteeringBehavior()){
                case CONTINUE:
                    info = record[i].printInfo();
                    outFile << time << "," << info << endl;
                    break;
                case SEEK:
                    Character *targ = record[i].getTarget();

                    Coord steer = movement.seek(targ, record[i]);
                    
                    float angle = (tanl(steer.z/steer.x) * 180 * PI) - 90;
                    record[i].update(deltaTime, steer, angle);
                    info = record[i].printInfo();
                    outFile << time << "," << info << endl;
                    break;
            }
        }

    }

    
    return 0;

}