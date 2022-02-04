#include "character.hpp"

struct Dynamic{

    Coord seek(Character *target, Character mover){
        Coord linear = target->getPos() - mover.getPos();
        linear.normalize();
        linear = linear * mover.getMaxLinear();

        return linear;
    }
};