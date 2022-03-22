#ifndef NODE_HPP
#define NODE_HPP

#include "helper.hpp"

class Node{
    private:
        int number, status, costSoFar, estTotal, plotPos, namePlotPos;
        float  estHeuristic;
        int prevNode;
        Coord pos;
        string name;
    
    public:
        Node();
        Node(int n, Coord p, int positionPlot, int posPlotName, string s);
        string printInfo();
        
        int getNumber();
        int getCostSoFar();
        Coord getPos();
        int getTotal();
        float getHeuristic();
        int getStatus();
        int getPrevNode();


        void setStatus(int n);
        void setCostSoFar(int n);
        void setPrevNode(int n);
        void setHeuristic(float n);

        void updateTotal();

};

#endif