#include "graph.hpp"

void Graph::addNode(Node* n){
    if(graph.find(n) != graph.end()){
        graph[n].clear();
    }
}

void Graph::addConnection(Connection* c, Node* n){
    graph[n].push_back(c);
}
