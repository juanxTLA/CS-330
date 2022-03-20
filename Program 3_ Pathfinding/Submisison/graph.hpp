#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "helper.hpp"
#include "node.cpp"
#include "connection.cpp"
#include <unordered_map>

//We will store nodes in a map that contains nodes as keys and retrieves a connection object
//from Millington, we need to ve able to retreive the connections of a node given that node

class Graph{
    private:
        unordered_map<Node*, vector<Connection*>> graph;

    public:
        void addNode(Node* n);
        void addConnection(Connection* c, Node* n);
};


#endif