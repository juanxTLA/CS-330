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

    Coord followPath(Character mover, Path path){
        float i = 1;
        
        float currentParam = getPathParam(path, mover.getPos());
        float targetParam = min(i, currentParam + mover.getPathOffset());
        Coord targetPos = getPathPos(path, targetParam);
        //reimplement dynamic seeks
        Coord linear = targetPos - mover.getPos();
        linear.normalize();
        linear = linear * mover.getMaxLinear();

        return linear;
    }
};

int main(){
    //open output file
    ofstream outFile;
    outFile.open("trajectory_data.txt");
    //vector to store characters
    vector<Character> record;
    vector<Coord> pts = {{0,90}, {-20, 65}, {20,40}, {-40,15}, 
                        {40, -10}, {-60,-35}, {60, -60}, {0,-85}};

    Character follow(2701, {0,0}, {20,95}, {0,0}, 0, FOLLOW, false, NULL, 2, 4);
    follow.setPathOffset(0.04);
    record.push_back(follow);
    Path path = assemblePath(pts, 1);

    Dynamic movement;
    //simulation variables
    double time = 0;
    double deltaTime = 0.5;
    double stopTime = 125;

    Character *targ; //target character helper variable
    Coord steer; //this is where we will hold the Coordinates for the movement algorithms
    //string to hold the character information
    string info;
    
    while(time < stopTime){
        time += deltaTime;
        for(int i = 0; i < record.size(); i++){
            switch (record[i].getSteeringBehavior()){
                case FOLLOW:
                    steer = movement.followPath(record[i], path);
                    
                    record[i].update(deltaTime, steer);
                    info = record[i].printInfo();
                    outFile << time << "," << info << endl;
                    break;
            }
        }

    }

    return 0;

}