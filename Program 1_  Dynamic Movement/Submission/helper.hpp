#ifndef HELPER_HPP
#define HELPER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>

#define PI  3.1416
typedef float rad;

struct Coord{
    float x, z;
    void normalize(){
        float mod = sqrt(abs(x*x) + abs(z*z)); 

        if (mod == 0){
            x = 0;
            z = 0;
            return;
        }

        x = x/mod;
        z = z/mod;
    }
};

float mod(Coord &a){
    return sqrt(abs(a.x*a.x) + abs(a.z*a.z));
}

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

#endif