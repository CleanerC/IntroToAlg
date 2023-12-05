#include "Graph.h"

void Graph::initVertices(int V) {
    Graph::numVertices = V;
    adj = new std::vector<std::pair<int, int>>[V];
}

int Graph::getNumVertices() {
    return Graph::numVertices;
}

void Graph::setNumEdges(int E) {
    Graph::numEdges = E;
}

int Graph::getNumEdges() {
    return Graph::numEdges;
}

Graph::Graph() {
    Graph::numVertices = 0;
    Graph::numEdges = 0;
}

void Graph::addEdge(int v, int u, int weight) {
    Graph::adj[v].push_back(std::make_pair(u, weight));
    Graph::adj[u].push_back(std::make_pair(v, weight));
}


void Graph::generateGraph(std::string fileName) {
    std::ifstream fd(fileName);
    std::string line;
    std::getline(fd, line);
    std::stringstream ss(line);
    int V, E;
    ss >> V >> E;
    Graph::initVertices(V);
    Graph::setNumEdges(E);
    while (std::getline(fd, line)) {
        std::stringstream ss(line);
        int v, u, weight;
        ss >> v >> u >> weight;
        Graph::addEdge(v, u, weight);
    }
}

void Graph::print() {
    for(int ii = 0; ii < this->getNumVertices(); ii++) {
        std::cout<< ii << ": ";
        for(int jj = 0; jj < this->adj[ii].size(); jj++) {
            int first = this->adj[ii][jj].first;
            int second = this->adj[ii][jj].second;
            std::cout<< first << " (" << second << ") ";
        }
        std::cout << "\n";
    }
}

void Graph::numShortestPaths(int source) {
    //initalize all the arrays
    int distance[this->getNumVertices()];
    int paths[this->getNumVertices()];
    
    //set every memeber to MAX
    std::fill_n(distance, this->getNumVertices(), MAX);
    std::fill_n(paths, this->getNumVertices(), MAX); 

    //set the source to be 0
    distance[source] = 0;
    //defult to be 1 paths
    paths[source] = 1;

    //make a min_priority_queue
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int, int>>, compare> pq;
    //push the source to the queue
    pq.push(std::make_pair(source, distance[source]));

    while(!pq.empty()) {
        //find the min on in the queue
        int focus = (pq.top()).first;
        pq.pop();
        //loop through every edges connecting focus
        for(int ii = 0; ii < adj[focus].size(); ii++) {
            //find the distance to the child vetex
            int dis = distance[focus] + adj[focus][ii].second;
            //if dis is shorter than the distance from the focus to that vertex
            if(dis < distance[adj[focus][ii].first]) {
                //update the distance on the array, and then push the pair on to the pq
                distance[adj[focus][ii].first] = dis;
                pq.push(std::make_pair(adj[focus][ii].first, dis));
                // set the path to the child to however many min paths to the focus
                paths[adj[focus][ii].first] = paths[focus]; 
            } else if (dis == distance[adj[focus][ii].first]) {
                //if the distance is equal to the one on the array, update the paths to the child vertex
                paths[adj[focus][ii].first] = paths[adj[focus][ii].first] + paths[focus];
            }
        }
    }
    //to Print
    std::cout << "\nShortest paths from node " << source <<":\n";
    for(int ii = 0; ii < this->getNumVertices(); ii++) {
        if(ii != source) {
            std::cout<< "Distance to vertex " << ii << " is " << distance[ii] << " and there are " << paths[ii] << " shortest paths\n";
        }
    }
}