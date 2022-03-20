#include "helper.hpp"
#include "graph.cpp"
#include <sstream>
#include <iterator>


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

    outFile << "CS 330, Pathfinding" << endl << endl;

    //map to retreive a node given its node number for when we 
    unordered_map<int, Node*> nodeCollection;

    Graph adventureBay;
    string line;
    vector<string> words;
    outFile << "Nodes" << endl;
    while(getline(nodesFile, line)){
        
        if(line[0] != '#'){ //if it is not a comment
            int num, pos1, pos2;
            Coord pos;
            line.erase(remove(line.begin(), line.end(), ','), line.end());
            // Wrap text in stream.
            istringstream iss{line};
            // Read tokens from stream into vector (split at whitespace).
            vector<string> words{istream_iterator<string>{iss}, istream_iterator<string>{}};

            string nodeName;
            for(int i = 11; i < words.size(); i++){
                nodeName += words[i];
            }

            nodeName.erase(remove(nodeName.begin(), nodeName.end(), '\"'), nodeName.end());

            num = stoi(words[1]);
            pos = {stof(words[7]), stof(words[8])};
            pos1 = stoi(words[9]);
            pos2 = stoi(words[10]);
            Node* newNode = new Node(num, pos, pos1, pos2, nodeName);
            nodeCollection[newNode->getNumber()] = newNode;
            adventureBay.addNode(newNode);

            outFile << "N " << newNode->printInfo() << endl;
            words.clear();
        }
    }

    outFile << "\nConnections" << endl;
    while(getline(connectionsFile, line)){
        if(line[0] != '#'){ //if it is not a comment
            int num, type, cost, pos;
            Node* from, *to;
            line.erase(remove(line.begin(), line.end(), ','), line.end());
            // Wrap text in stream.
            istringstream iss{line};
            // Read tokens from stream into vector (split at whitespace).
            vector<string> words{istream_iterator<string>{iss}, istream_iterator<string>{}};

            num = stoi(words[1]);
            from = nodeCollection[stoi(words[2])];            
            to = nodeCollection[stoi(words[3])];
            cost = stoi(words[4]);
            pos = stoi(words[5]);
            type = stoi(words[6]);         

            Connection* newConnection = new Connection(cost, num, pos, type, from, to);
            adventureBay.addConnection(newConnection, from);

            outFile << "C " << newConnection->getNumber() << " " << newConnection->getFromNode()->getNumber() << " " <<
                newConnection->getToNode()->getNumber() << " " << newConnection->getCost() << " " << newConnection->getPos() <<
                " " << newConnection->getType() << endl;
            
            words.clear();
        }
    }

    //algorithm begins
    
    return 0;
}