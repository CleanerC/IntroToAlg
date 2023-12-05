//
//  Graph.h
//
//  Created by Tali Moreshet
//

#ifndef Graph_h
#define Graph_h

#define MAX 99999

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

/* Implements an undirected, weighted graph */
class Graph {
    
public:
    /* added */
    class compare{
         public:
            bool operator()(std::pair<int, int> left, std::pair<int,int> right) {
               return (left.second > right.second);
            }
    };
    

    /* Constructs an empty graph */
    Graph();
        
    /* Initializes the graph to contain V vertices */
    void initVertices(int V);

    /* Returns the number of vertices in the graph */
    int getNumVertices();
        
    /* Sets the number of edges of the graph */
    void setNumEdges(int E);
        
    /* Returns the number of edges in the graph */
    int getNumEdges();
        
    /* Adds the given edge with the provided weight to the graph.
       The vertices of the new edge must currently exist in the graph. */
    void addEdge(int v, int u, int weight);
    
    /* Prints a human-readable version of the adjacency list of the graph.
     Format is: vertex: adjacent_vertex_1 (weight_1) adjacent_vertex_2 (weight_2) ... */
    void print();
    
    /* Constructs a graph from the file with the provided name.
       The file format is as follows: 
       The first line contains the number of vertices and the number of edges, separated by a space,
        followed by optional additional text.
       The graph is assumed to contain vertices numbered 0 to 'number of vertices' - 1.
       Each of the remaining lines contain one edge specified by the source and destination vertices 
         followed by the weight, and separated by spaces.  */
    void generateGraph(string fileName);
    
    /* Prints the weight and number of shortest paths from provided source to all other nodes for the graph.
       Assuming that the graph is guaranteed to have non-negative weight edges, and source is a vertex of the graph. */
    void numShortestPaths(int source);
      
private:
    int numVertices;                        /* Number of vertices */
    int numEdges;                           /* Number of edges */
    vector<pair<int, int>> *adj;           /* Adjacency list rep of the graph */
};


#endif /* Graph_h */