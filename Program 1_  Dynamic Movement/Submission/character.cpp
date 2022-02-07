#include "character.hpp"

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

//getters
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

Coord Character::getLinear(){
    return acceleration;
}

rad Character::getOrientation(){
    return orientation;
}

float Character::getArriveRadius(){
    return arrivingRadius;
}

float Character::getSlowRadius(){
    return slowingRadius;
}

float Character::getTime(){
    return timeTarget;
}

float Character::getMaxVel(){
    return maxVelocity;
}

Coord Character::getVelocity(){
    return velocity;
}
//setters
void Character::setRadius(float arr, float slow){
    arrivingRadius = arr;
    slowingRadius = slow;
}

void Character::setTime(float t){
    timeTarget = t;
}
//rest
std::string Character::printInfo(){
    std::string out;
    string col = colided ? "TRUE" : "FALSE";
    out = to_string(id) + "," + to_string(pos.x) + "," + to_string(pos.z) + "," + to_string(velocity.x) + "," 
        + to_string(velocity.z) + "," + to_string(acceleration.x) + "," + to_string(acceleration.z)
        + "," + to_string(orientation) + "," + to_string(steeringBehavior) + "," + col;
    
    return out;
}

void Character::update(float deltaTime, Coord linear){
    pos = pos + (velocity * deltaTime);
    velocity = velocity + (linear * deltaTime);
    if(mod(velocity) > maxVelocity){
        velocity.normalize();
        velocity = velocity * maxVelocity;
    } 


    acceleration = linear;

    if(mod(velocity) <= MIN_VEL){
        velocity = {0,0};
    }
    
}