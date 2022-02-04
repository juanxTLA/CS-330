
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <math.h>

struct Coord{
    float x, z;

    //float mod = sqrt(abs(x*x) + abs(z*z)); 

    void normalize(){
        float mod = sqrt(abs(x*x) + abs(z*z));
        x = x/mod;
        z = z/mod;
    }
};

inline Coord operator+(Coord const &a, Coord const &b){
    Coord res;
    res.x = a.x + b.x;
    res.z = a.z + b.z;

    return res;
}

inline Coord operator-(Coord const &a, Coord const &b){
    Coord res;
    res.x = a.x - b.x;
    res.z = a.z - b.z;

    return res;
}

inline Coord operator*(Coord const &a, float scalar){
    Coord res;
    res.x = a.x * scalar;
    res.z = a.z * scalar;

    return res;
}


enum SteeringBehavior {
    CONTINUE = 1,
    SEEK = 6,
    FLEE = 7,
    ARRIVE = 8
};

typedef float rad;

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
        
        

    public:

        Character(int uid, Coord vel, Coord position, Coord acc, rad orien, SteeringBehavior steer, bool col, 
                    Character* targ, float maxAcc, float maxVel);
        
        std::string printInfo();
        
        void update(float deltaTime, Coord linear, float angle);

        Coord getPos();
        float getMaxLinear();
        int getId();
        Character* getTarget();
        SteeringBehavior getSteeringBehavior();
};

#endif