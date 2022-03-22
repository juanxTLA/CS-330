#include "connection.hpp"

Connection::Connection(int c, int n, int pos, int t, 
                        int from, int to){
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

int Connection::getToNode(){
    return toNode;
}

int Connection::getFromNode(){
    return fromNode;
}