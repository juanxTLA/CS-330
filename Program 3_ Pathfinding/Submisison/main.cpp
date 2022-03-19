#include "helper.hpp"
#include "graph.hpp"

int main(){
    ifstream nodesFile, connectionsFile;
    ofstream outFile;

    nodesFile.open("CS 330, Pathfinding, Graph AB Nodes v3.txt");
    connectionsFile.open("CS 330, Pathfinding, Graph AB Connections v3.txt");
    outFile.open("CS 330 22S, Program3, Output.txt");

    if(!nodesFile.is_open() or !connectionsFile.is_open()){
        cout << "Something went wrong openning the input files" << endl;
        return 0;
    }

    //map to retreive a node given its node number for when we 
    unordered_map<int, Node*> nodeCollection;

    Graph adventureBay;

    string line;
    while(!nodesFile.eof()){
        getline(nodesFile, line);
        if(line[0] != '#'){ //if it is not a comment
            Coord position = {stof(line[7]), stof(line[8])};
            adventureBay.addNode(new Node(stoi(line[1]), 
                                position, stoi(line[9]), 
                                stoi(line[10]), line[11]));
        }
    }


    return 0;
}