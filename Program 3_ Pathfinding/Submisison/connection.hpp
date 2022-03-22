#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "node.hpp"

class Connection{
    private:
        int cost, number, plotPos, type;
        int fromNode, toNode;
    public:
        Connection(int c, int n, int pos1, int t, 
                    int from, int to);

        int getCost();
        int getNumber();
        int getPos();
        int getType();

        int getFromNode();
        int getToNode();
};

#endif
