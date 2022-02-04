
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

struct Coord{
    float x, z;
};

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
        int target;

    public:

        Character(int uid, Coord vel, Coord position, Coord acc, rad orien, SteeringBehavior steer, bool col, int targ);
        
        std::string printInfo();
        
        void update();

        Coord getPos();
};

#endif