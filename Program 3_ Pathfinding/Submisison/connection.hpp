#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "node.hpp"

class Connection{
    private:
        int cost, number, plotPos, type;
        Node *fromNode, *toNode;
    public:
        Connection(int c, int n, int pos1, int t, 
                    Node* from, Node* to);

        int getCost();
        int getNumber();
        int getPos();
        int getType();

        Node* getFromNode();
        Node* getToNode();
};

#endif
