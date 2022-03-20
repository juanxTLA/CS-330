#include "connection.hpp"

Connection::Connection(int c, int n, int pos, int t, 
                        Node* from, Node* to){
    cost = c;
    number = n;
    plotPos = pos;
    type = t;

    fromNode = from;
    toNode = to;

}

int Connection::getCost(){
    return cost;
}

int Connection::getNumber(){
    return number;
}

int Connection::getType(){
    return type;
}

int Connection::getPos(){
    return plotPos;
}

Node* Connection::getToNode(){
    return toNode;
}

Node* Connection::getFromNode(){
    return fromNode;
}