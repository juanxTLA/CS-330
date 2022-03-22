#include "node.hpp"

Node::Node(int n, Coord p, int positionPlot, int posPlotName, string s){
    number = n;
    status = UNDEFINED;
    costSoFar = 0; 
    estHeuristic = 0;
    estTotal = 0;
    prevNode = 0;
    pos = p;
    name = s;
    plotPos = positionPlot;
    namePlotPos = posPlotName;
}

Node::Node(){}

string Node::printInfo(){
    std::string out;
    out = to_string(number) + " " + to_string(status) + " " + to_string(costSoFar) + " " + to_string(estHeuristic) + " " 
    + to_string(estTotal) + " " + to_string(0) + " " + to_string(pos.x)
    + " " + to_string(pos.z) + " " + to_string(plotPos) + " " + to_string(namePlotPos) + " " + name;

    return out;
}

int Node::getNumber(){
    return number;
}

Coord Node::getPos(){
    return pos;
}

int Node::getTotal(){
    return estTotal;
}

int Node::getCostSoFar(){
    return costSoFar;
}

int Node::getStatus(){
    return status;
}

int Node::getPrevNode(){
    return prevNode;
}

void Node::setCostSoFar(int n){
    costSoFar = n;
}

void Node::setStatus(int n){
    status = n;
}

void Node::setHeuristic(float n){
    estHeuristic = n;
}

void Node::updateTotal(){
    estTotal = estHeuristic + costSoFar;
}

void Node::setPrevNode(int n){
    prevNode = n;
}

