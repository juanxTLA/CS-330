#include "helper.hpp"
#include "node.cpp"
#include "connection.cpp"
#include <sstream>
#include <iterator>
#include <stack>

struct Graph{
    unordered_map<int, vector<Connection>> graph;
    unordered_map<int, Node> nodes;

    void addNode(Node n){
        if(nodes.find(n.getNumber()) == nodes.end()){
            nodes[n.getNumber()] = n;
            graph[n.getNumber()].clear();
        }
    }

    void addConnection(Connection c, int n){
        graph[n].push_back(c);
    }

    void addNodeCollection(unordered_map<int, Node> n){
        nodes = n;
    }

    Node getNode(int id){
        return nodes[id];
    }

    vector<Connection> getConnections(int n){
        return graph[n];
    }

    void initializeNodes(){
        for(int i = 0; i < nodes.size(); i++){
            nodes[i].setStatus(UNVISITED);
            nodes[i].setCostSoFar(INT_MAX);
        }
    }
};

struct AStar{
    //fine
    float heuristic(Node n1, Node n2){
        Coord d1 = n1.getPos();
        Coord d2 = n2.getPos();
        return distancePointPoint(d1, d2);
    }

    Node findLowest(Graph g, vector<Node> open){
        int minCost = INT_MAX;
        int res;
        for(int i = 0; i < open.size(); i++){
            if(open[i].getTotal() < minCost){
                minCost = open[i].getTotal();
                res = open[i].getNumber();
            }
        }

        return g.getNode(res);
    }

    Graph findPath(Graph g, int first, int last){
        //remember to print statement
        g.initializeNodes();
        vector<Node> openNodes;
        vector<Connection> currentConnections;
        //initialize first node
        g.nodes[first].setStatus(OPEN);
        g.nodes[first].setCostSoFar(0);
        openNodes.push_back(g.nodes[first]);
        //main loop
        while(!openNodes.empty()){
            Node currentNode = findLowest(g, openNodes);
            
            if(currentNode.getNumber() == last){
                break;
            }

            currentConnections = g.graph[currentNode.getNumber()];
            for(int i = 0; i < currentConnections.size(); i++){
                Connection c = currentConnections[i];
                Node toNode = g.getNode(c.getToNode());
                int toCost = currentNode.getCostSoFar() + c.getCost();

                if(toCost < toNode.getCostSoFar()){
                    g.nodes[toNode.getNumber()].setCostSoFar(toCost);
                    g.nodes[toNode.getNumber()].setStatus(OPEN);
                    g.nodes[toNode.getNumber()].setHeuristic(heuristic(toNode, g.getNode(last)));
                    g.nodes[toNode.getNumber()].updateTotal();
                    g.nodes[toNode.getNumber()].setPrevNode(currentNode.getNumber());
                    openNodes.push_back(g.nodes[toNode.getNumber()]);
                }

                g.nodes[currentNode.getNumber()].setStatus(CLOSED);
                for(int i = 0; i < openNodes.size(); i++){
                    if(openNodes[i].getNumber() == currentNode.getNumber()){
                        openNodes.erase(openNodes.begin() + i);
                    break;
                    }
                }

            }

        }

        return g;
    }

    
};


void retrievePath(Graph g, int f, int l, ofstream &out){
    int i = l;
    int cost = g.nodes[l].getCostSoFar();
    stack<int> p;
    while(i != 0){
        p.push(i);
        i = g.nodes[i].getPrevNode();
    }

    out << "\nPath from " << f << " to " << l << " path = ";
    while(!p.empty()){
        out << p.top() << " ";
        p.pop();
    }
    out << "cost = " << cost << endl;
}

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
    unordered_map<int, Node> nodeCollection;

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
            Node newNode = Node(num, pos, pos1, pos2, nodeName);
            adventureBay.addNode(newNode);

            outFile << "N " << newNode.printInfo() << endl;
            words.clear();
        }
    }

    outFile << "\nConnections" << endl;
    while(getline(connectionsFile, line)){
        if(line[0] != '#'){ //if it is not a comment
            int num, type, cost, pos;
            line.erase(remove(line.begin(), line.end(), ','), line.end());
            // Wrap text in stream.
            istringstream iss{line};
            // Read tokens from stream into vector (split at whitespace).
            vector<string> words{istream_iterator<string>{iss}, istream_iterator<string>{}};

            num = stoi(words[1]);
            Node from = adventureBay.getNode(stoi(words[2]));            
            Node to = adventureBay.getNode(stoi(words[3]));
            cost = stoi(words[4]);
            pos = stoi(words[5]);
            type = stoi(words[6]);         

            Connection newConnection(cost, num, pos, type, from.getNumber(), to.getNumber());
            adventureBay.addConnection(newConnection, from.getNumber());

            outFile << "C " << newConnection.getNumber() << " " << newConnection.getFromNode() << " " <<
                newConnection.getToNode() << " " << newConnection.getCost() << " " << newConnection.getPos() <<
                " " << newConnection.getType() << endl;
            
            words.clear();
        }
    }
    AStar aStar;
    Graph g1 = aStar.findPath(adventureBay, 1, 29);
    Graph g2 = aStar.findPath(adventureBay, 1, 38);
    Graph g3 = aStar.findPath(adventureBay, 11, 1);
    Graph g4 = aStar.findPath(adventureBay, 33, 16);
    Graph g5 = aStar.findPath(adventureBay, 58, 43);

    retrievePath(g1, 1, 29, outFile);  
    retrievePath(g2, 1, 38, outFile);  
    retrievePath(g3, 11, 1, outFile);  
    retrievePath(g4, 33, 16, outFile);  
    retrievePath(g5, 58, 43, outFile);  

    return 0;
}