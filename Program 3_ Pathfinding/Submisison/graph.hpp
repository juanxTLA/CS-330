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
        unordered_map<int, vector<Connection>> graph;
        unordered_map<int, Node> nodes;

    public:
        Graph();
        void addNode(int n);
        void addConnection(Connection c, int n);
        void addNodeCollection(unordered_map<int, Node> n);
        void initializeNodes();
        Node getNode(int id);

        vector<Connection> getConnections(int n);
};


#endif