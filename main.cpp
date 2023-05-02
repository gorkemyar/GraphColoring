#include <iostream>
#include <string>
#include "graph.h"
#include "courses/courses.h"
using namespace std;

typedef void (Graph<string>::*algorithm)();

// function declarations

template<typename type>
algorithm findAlgorithm(Graph<type> & g, char type1);

template<typename type>
void create_random_colors(Graph<type> & g);

template<typename type>
void print_results(Graph<type> & g);

template<typename type>
void testCase(Graph<type> & g, char type1);


int main(int argc, char** argv){
    
    int node_count = 30;
    int edge_count = 100;
    char algo = 'g';

    if (argc > 1) {
        node_count = stoi(argv[1]);
    }
    if (argc > 2) {
        edge_count = stoi(argv[2]);
    }if (argc > 3) {
        algo = argv[3][0];
    }

    Courses courses({"CS", "EE", "MATH", "PHYS", "CHEM", "BIO", "IE", "ME"});
    
    Graph<string> g;
    g.create_random_graph(node_count, edge_count, [&](int i){return courses.generate_random_course();});

    // Check if the graph is connected
    if (g.isConnected()) {
        cout << "Graph is connected." << endl;
    } else {
        cout << "Graph is not connected." << endl;
    }
    
    testCase<string>(g, algo);
    g.printGraphJson(); 

    return 0;
}

// function implementations 

template<typename type>
algorithm findAlgorithm(Graph<type> & g, char type1){
    switch (type1)
    {
    case 'g':
        cout<<"Greedy"<<endl;
        return &Graph<type>::greedy_coloring;
        break;
    case 'd':
        cout<<"Dsatur"<<endl;
        return &Graph<type>::Dsatur_coloring;
        break;
    case 's':
        return &Graph<type>::SDL_coloring;
        break;
    case 'w':
        cout<<"Welsh Powell"<<endl;
        return &Graph<type>::welsh_powell_coloring;
        break;
    default:
        return &Graph<type>::greedy_coloring;
        break;
    }
}

template<typename type>
void print_results(Graph<type> & g){
    if (g.check_coloring()) {
        cout << "Valid coloring!" << endl;
    } else {
        cout << "Invalid coloring!" << endl;
    }

    cout << "Number of unique colors in graph: " << g.countColors() << endl;
    g.print_coloring();
}

template<typename type>
void testCase(Graph<type> & g, char type1){
      //heuristic coloring
    algorithm alg = findAlgorithm<type>(g, type1);
    (g.*alg)();
    print_results<type>(g);
}

template<typename type>
void create_random_colors(Graph<type> & g){
    vector<node<type>*> vertexes = g.getVertexes();
    for (auto n : vertexes) {
        n->color = g.generate_random_color();
    }
}

