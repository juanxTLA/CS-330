// Project:  Programming assignment 1
// Author:  Juan Tarrat and Julio Rivera

#include "character.cpp"
#include "helper.hpp"


using namespace std;

//this struct holds the different movement algorithms
struct Dynamic{

    Coord seek(Character *target, Character mover){
        Coord linear = target->getPos() - mover.getPos();
        linear.normalize();
        linear = linear * mover.getMaxLinear();

        return linear;
    }

    Coord flee(Character *target, Character mover){
        Coord linear = target->getPos() + mover.getPos();
        linear.normalize();
        linear = linear * mover.getMaxLinear();

        return linear;
    }

    Coord arrive(Character *target, Character mover){
        Coord linear = target->getPos() - mover.getPos();
        float dist = mod(linear);

        float arrSpeed;

        if(dist < mover.getArriveRadius()){
            arrSpeed = 0;
        } 
        else if (dist > mover.getSlowRadius()) arrSpeed = mover.getMaxVel();
        else arrSpeed = mover.getMaxVel() * dist / mover.getSlowRadius();

        Coord arrVel = linear;
        arrVel.normalize();
        arrVel = arrVel * arrSpeed;
        linear = arrVel - mover.getVelocity();
        linear = linear / mover.getTime();
        
        if(mod(linear) > mover.getMaxLinear()){
            linear.normalize();
            linear = linear * mover.getMaxLinear();
        }

        return linear;

    }
};

int main(){
    //open output file
    ofstream outFile;
    outFile.open("trajectory_data.txt");
    //vector to store characters
    vector<Character> record;

    //Create continue character
    Character cont = Character(2601, {0,0}, {0,0}, {0,0}, 0, CONTINUE, false, NULL, 0,0);
    //Create flee character
    Character flee = Character(2602, {2,7}, {-30,-50}, {0,0}, PI/4, FLEE, false, &cont, 1.5, 8); 
    //create seek character
    Character seek = Character(2603, {0,8}, {-50,40}, {0,0}, 3*PI/2, SEEK, false, &cont, 2, 8);
    //create arrive character
    Character arrive = Character(2604, {-9,4}, {50,75}, {0,0}, PI, ARRIVE, false, &cont, 2, 10);
    //set radius for arrive character
    arrive.setRadius(4, 32);
    arrive.setTime(1);
    //store them in the vector
    record.push_back(cont);
    record.push_back(seek);
    record.push_back(flee);
    record.push_back(arrive);

    Dynamic movement;
    //simulation variables
    double time = 0;
    double deltaTime = 0.5;
    double stopTime = 50;

    Character *targ; //target character helper variable
    Coord steer; //this is where we will hold the Coordinates for the movement algorithms
    //string to hold the character information
    string info;

    while(time < stopTime){
        time += deltaTime;
        for(int i = 0; i < record.size(); i++){
            switch(record[i].getSteeringBehavior()){
                case CONTINUE:
                    info = record[i].printInfo();
                    outFile << time << "," << info << endl;
                    break;
                case FLEE:
                    targ = record[i].getTarget();

                    steer = movement.flee(targ, record[i]);
                    record[i].update(deltaTime, steer);
                    info = record[i].printInfo();
                    outFile << time << "," << info << endl;
                    break;
                
                case SEEK:
                    targ = record[i].getTarget();

                    steer = movement.seek(targ, record[i]);
                    
                    record[i].update(deltaTime, steer);
                    info = record[i].printInfo();
                    outFile << time << "," << info << endl;
                    break;

                case ARRIVE:
                    targ = record[i].getTarget();
                    steer = movement.arrive(targ, record[i]);
                    
                    record[i].update(deltaTime, steer);
                    info = record[i].printInfo();
                    outFile << time << "," << info << endl;
                    break;
            }
        }

    }

    
    return 0;

}