#include "graph.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
    // Graph<int> g;
    // g.addNode(1);
    // g.addNode(2);
    // g.addNode(3);
    // g.addNode(4);


    // g.addEdgeUndirected(1,2,1);
    // g.addEdgeUndirected(1,3,1);
    // g.addEdgeUndirected(2,3,1);
    // g.addEdgeUndirected(2,4,1);
    // g.addEdgeUndirected(3,4,1);


    // Create a graph with 10 nodes and 20 random edges
    Graph<int> g;
    g.create_random_graph(10, 20, [](int i){ return i; });

    // Check if the graph is connected
    if (g.isConnected()) {
        cout << "Graph is connected." << endl;
    } else {
        cout << "Graph is not connected." << endl;
    }

    // Print the graph
    cout << "The graph:" << endl;
    g.printGraph();

    // Generate random colors for each node
    cout << "Generating random colors for each node:" << endl;
    vector<node<int>*> vertexes = g.getVertexes();
    for (auto n : vertexes) {
        n->color = g.generate_random_color();
    }

    //check if coloring is valid (it should be since random color generator adds unique color for each node)
    if (g.check_coloring()) {
        cout << "Valid coloring!" << endl;
    } else {
        cout << "Invalid coloring!" << endl;
    }

    cout << "Number of unique colors in graph: " << g.countColors() << endl;

    //heuristic coloring
    g.greedy_coloring();
    g.print_coloring();

    if (g.check_coloring()) {
        cout << "Valid coloring!" << endl;
    } else {
        cout << "Invalid coloring!" << endl;
    }

    cout << "Number of unique colors in graph: " << g.countColors() << endl;

    return 0;
}

// To run this code, compile it with:
// g++ main.cpp -o main -std=c++11
// Then run it with:
// ./main