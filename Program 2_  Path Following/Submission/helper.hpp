#ifndef HELPER_HPP
#define HELPER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
//define global variables
#define PI  3.1416
#define MIN_VEL 0.02

using namespace std;

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

inline float operator*(Coord const &a, Coord const &b){
    return (a.x * b.x) + (a.z * b.z);
}
//collection of behaviors
enum SteeringBehavior {
    CONTINUE = 1,
    SEEK = 6,
    FLEE = 7,
    ARRIVE = 8,
    FOLLOW = 11
};

float distancePointPoint(Coord A, Coord B){
    float a2, b2;
    a2 = (B.x - A.x) * (B.x - A.x);
    b2 = (B.z - A.z) * (B.z - A.z);
    return sqrt(a2 + b2);
}

Coord closestPointSegment(Coord q, Coord a, Coord b){
    float t = ((q - a) * (b - a)) / ((b - a) * (b - a));

    if(t <= 0) return a;
    else if (t >= 1) return b;
    else return a + ((b - a) * t);
}

struct Path{
    int id, segments;
    vector<Coord> points;
    vector<float> distance;
    vector<float> param;
};

Path assemblePath(vector<Coord> p, int i){
    Path path;
    path.id = i;
    path.points = p;
    path.segments = path.points.size() - 1;
    
    path.distance.push_back(0);
    path.param.push_back(0);

    for(int i = 1; i < path.segments + 1; i++){
        float dis = distancePointPoint(path.points[i - 1], path.points[i]);
        path.distance.push_back(dis + path.distance[i - 1]); 
    }

    for(int i = 1; i < path.segments + 1; i++){
        path.param.push_back(path.distance[i] / path.distance.back());
    }

    return path;
}

Coord getPathPos(Path path, float param){
    int j = 0;
    for(int i = path.param.size() - 1; i >= 0; i--){
        if(param > path.param[i]){
            j = i;
            break;
        }
    }
    Coord a = path.points[j];
    Coord b = path.points[j+1];

    float t = (param - path.param[j]) / (path.param[j + 1] - path.param[j]);

    return a + ((b - a) * t);
}

float getPathParam(Path path, Coord pos){
    float closestDist = INT64_MAX;

    Coord closestPoint;
    int closestSegment;

    for(int i = 0; i < path.segments; i++){
        Coord a = path.points[i];
        Coord b = path.points[i+1];

        Coord checkPoint = closestPointSegment(pos, a, b);
        float checkDist = distancePointPoint(pos, checkPoint);

        if(checkDist < closestDist){
            closestPoint = checkPoint;
            closestDist = checkDist;
            closestSegment = i;
        }
    }

    Coord a = path.points[closestSegment];
    float aParam = path.param[closestSegment];

    Coord b = path.points[closestSegment + 1];
    float bParam = path.param[closestSegment + 1];

    Coord c = closestPoint;

    Coord sub1 = c - a;
    Coord sub2 = b - a;
    float t = mod(sub1) / mod(sub2);

    return aParam + t * (bParam - aParam);

}


#endif