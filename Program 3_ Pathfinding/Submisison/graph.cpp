#include "graph.hpp"

void Graph::addNode(int n){
    if(graph.find(n) != graph.end()){
        graph[n].clear();
    }
}

void Graph::addConnection(Connection c, int n){
    graph[n].push_back(c);
}

void Graph::addNodeCollection(unordered_map<int, Node> n){
    nodes = n;
}

Node Graph::getNode(int id){
    return nodes[id];
}

vector<Connection> Graph::getConnections(int n){
    return graph[n];
}

void Graph::initializeNodes(){
    for(int i = 0; i < nodes.size(); i++){
        nodes[i].setStatus(UNVISITED);
        nodes[i].setCostSoFar(INT_MAX);
    }
}