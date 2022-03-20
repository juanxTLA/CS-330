#ifndef NODE_HPP
#define NODE_HPP

#include "helper.hpp"

class Node{
    private:
        int number, status, costSoFar, estHeuristic, estTotal, plotPos, namePlotPos;
        Node* prevNode;
        Coord pos;
        string name;
    
    public:
        Node(int n, Coord p, int positionPlot, int posPlotName, string s);
        string printInfo();
        
        int getNumber();
};

#endif