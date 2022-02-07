#ifndef HELPER_HPP
#define HELPER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
//define global variables
#define PI  3.1416
#define MIN_VEL 0.02

typedef float rad;
//define coordinate structure with x and z
//this will serve as vector
//also has a function for normalize
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
//function to find the length of a vector
float mod(Coord &a){
    return sqrt(a.x*a.x + a.z*a.z);
}
//redefine operators to make operations easier to perform
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

inline Coord operator/(Coord const &a, float scalar){
    Coord res;
    res.x = a.x / scalar;
    res.z = a.z / scalar;

    return res;
}

//collection of behaviors
enum SteeringBehavior {
    CONTINUE = 1,
    SEEK = 6,
    FLEE = 7,
    ARRIVE = 8
};

#endif