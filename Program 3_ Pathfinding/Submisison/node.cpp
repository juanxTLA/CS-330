#include "node.hpp"

Node::Node(int n, Coord p, int positionPlot, int posPlotName, string s){
    number = n;
    status = 0;
    costSoFar = 0; 
    estHeuristic = 0;
    estTotal = 0;
    prevNode = NULL;
    pos = p;
    name = s;
    plotPos = positionPlot;
    namePlotPos = posPlotName;
}

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