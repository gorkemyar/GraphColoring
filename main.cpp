#include "graph.h"
#include <iostream>
#include <string>

using namespace std;

typedef void (Graph<int>::*algorithm)();

algorithm findAlgorithm(char type){
    switch (type)
    {
    case 'g':
        return &Graph<int>::greedy_coloring;
        break;
    case 'm':
        return &Graph<int>::greedy_coloring_min_available_color;
        break;
    default:
        return &Graph<int>::greedy_coloring;
        break;
    }
}

void create_random_colors(Graph<int> & g){
    vector<node<int>*> vertexes = g.getVertexes();
    for (auto n : vertexes) {
        n->color = g.generate_random_color();
    }
}


void print_results(Graph<int> & g){
    if (g.check_coloring()) {
        cout << "Valid coloring!" << endl;
    } else {
        cout << "Invalid coloring!" << endl;
    }

    cout << "Number of unique colors in graph: " << g.countColors() << endl;
    g.print_coloring();
}
void testCase(Graph<int> & g, char type){
      //heuristic coloring
    algorithm alg = findAlgorithm('g');
    (g.*alg)();
    print_results(g);
}




int main(){

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
  
    //heuristic coloring
    // test available algorithms
    // g: greedy_coloring
    // m: greedy_coloring_min_available_color
    testCase(g, 'g');
    return 0;
}
