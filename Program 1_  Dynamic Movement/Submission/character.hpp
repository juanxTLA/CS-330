
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "helper.hpp"

class Character{
    private:
        int id;
        Coord velocity;
        Coord pos;
        Coord acceleration;
        rad orientation;
        SteeringBehavior steeringBehavior;
        bool colided;
        float maxLinear, maxVelocity;
        Character* target;

        float arrivingRadius, slowingRadius, timeTarget;
    public:

        Character(int uid, Coord vel, Coord position, Coord acc, rad orien, SteeringBehavior steer, bool col, 
                    Character* targ, float maxAcc, float maxVel);
        

        std::string printInfo();
        void update(float deltaTime, Coord linear, float angle);

        Coord getPos();
        float getMaxLinear();
        float getMaxVel();
        int getId();
        Character* getTarget();
        SteeringBehavior getSteeringBehavior();
        Coord getLinear();
        rad getOrientation();
        float getArriveRadius();
        float getSlowRadius();
        float getTime();
        Coord getVelocity();

        void setRadius(float arr, float slow);
        void setTime(float t);
};

#endif