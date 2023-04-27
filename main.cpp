#include "graph.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
    Graph<int> g;
    // g.addNode(1);
    // g.addNode(2);
    // g.addNode(3);
    // g.addNode(4);


    // g.addEdgeUndirected(1,2,1);
    // g.addEdgeUndirected(1,3,1);
    // g.addEdgeUndirected(2,3,1);
    // g.addEdgeUndirected(2,4,1);
    // g.addEdgeUndirected(3,4,1);


    g.create_random_graph(30, 40, [](int i){return i;});
    g.printGraph();

    if (g.isConnected())
        cout << "Graph is connected" << endl;
    else
        cout << "Graph is not connected" << endl;

    return 0;
}


// To run this code, compile it with:
// g++ main.cc -o main -std=c++11
// Then run it with:
// ./main