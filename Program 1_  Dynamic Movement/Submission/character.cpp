#include "character.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Character::Character(int uid, Coord vel, Coord position, Coord acc, 
                        rad orien, SteeringBehavior steer, bool col, Character* targ, float maxAcc, float maxVel){
    id = uid;
    velocity = vel;
    pos = position;
    acceleration = acc;
    orientation = orien;
    steeringBehavior = steer;
    colided = col;
    target = targ;
    maxLinear = maxAcc;
    maxVelocity = maxVel;
}

void Character::update(float deltaTime, Coord linear, rad angle){
    pos = pos + (velocity * deltaTime);
    velocity = velocity + (linear * deltaTime);
   // if(velocity.mod > maxVelocity){
      // velocity = velocity.normalize() * maxVelocity;
    //} 
    orientation = angle;
    acceleration = linear;
}

Coord Character::getPos(){
    return pos;
}

float Character::getMaxLinear(){
    return maxLinear;
}

int Character::getId(){
    return id;
}

Character* Character::getTarget(){
    return target;
}

SteeringBehavior Character::getSteeringBehavior(){
    return steeringBehavior;
}

std::string Character::printInfo(){
    std::string out;
    string col = colided ? "TRUE" : "FALSE";
    out = to_string(id) + "," + to_string(pos.x) + "," + to_string(pos.z) + "," + to_string(velocity.x) + "," 
        + to_string(velocity.z) + "," + to_string(acceleration.x) + "," + to_string(acceleration.z)
        + "," + to_string(orientation) + "," + to_string(steeringBehavior) + "," + col;
    
    return out;
}
