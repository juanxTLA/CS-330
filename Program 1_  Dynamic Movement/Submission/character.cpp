#include "character.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Character::Character(int uid, Coord vel, Coord position, Coord acc, 
                        rad orien, SteeringBehavior steer, bool col, int targ){
    id = uid;
    velocity = vel;
    pos = position;
    acceleration = acc;
    orientation = orien;
    steeringBehavior = steer;
    colided = col;
    target = targ;
}

void Character::update(){

}

Coord Character::getPos(){
    return pos;
}

std::string Character::printInfo(){
    std::string out;
    string col = colided ? "TRUE" : "FALSE";
    out = to_string(id) + "," + to_string(pos.x) + "," + to_string(pos.z) + "," + to_string(velocity.x) + "," 
        + to_string(velocity.z) + "," + "," + to_string(acceleration.x) + "," + to_string(acceleration.z)
        + "," + to_string(orientation) + "," + col;
    
    return out;
}
