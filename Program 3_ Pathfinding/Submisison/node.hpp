#ifndef NODE_HPP
#define NODE_HPP

#include "helper.hpp"
#include "connection.hpp"



class Node{
    private:
        int number, status, costSoFar, estHeuristic, estTotal, plotPos, namePlotPos;
        Node* prevNode;
        Coord pos;
        string name;
    
    public:
        Node(int n, Coord p, int positionPlot, int posPlotName, string s){
            number = n;
            status, costSoFar, estHeuristic, estTotal = 0;
            prevNode = NULL;
            pos = p;
            name = s;
            plotPos = positionPlot;
            namePlotPos = posPlotName;
        }
};

#endif