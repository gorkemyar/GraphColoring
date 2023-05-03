#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include "graph/graph.h"
#include "courses/courses.h"
#include "iomanip"
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

template<typename type>
void run_all_algorithms_and_save_timings(function<type(int)> random);

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

    // // Check if the graph is connected
    if (g.isConnected()) {
        cout << "Graph is connected." << endl;
    } else {
        cout << "Graph is not connected." << endl;
    }
    
    g.printGraph();


    testCase<string>(g, algo);
    g.printGraphJson(); 

    //run_all_algorithms_and_save_timings<string>([&](int i){return courses.generate_random_course();});
    
    return 0;
}

// function implementations 

template<typename type>
algorithm findAlgorithm(Graph<type> & g, char type1){
    switch (type1)
    {
    case 'g':
        return &Graph<type>::greedy_coloring;
        break;
    case 'd':
        return &Graph<type>::dsatur_coloring;
        break;
    case 's':
        return &Graph<type>::SDL_coloring;
        break;
    case 'w':
        return &Graph<type>::welsh_powell_coloring;
        break;
    case 'r':
        return &Graph<type>::rlf_coloring;
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

template<typename type>
void run_all_algorithms_and_save_timings(function<type(int)> random) {
    std::vector<char> algo_types = {'g', 'd', 's', 'w', 'r'};
    std::vector<std::string> algo_names = {"Greedy", "Dsatur", "SDL", "Welsh_Powell", "RLF"};

    std::ofstream outfile("results/algo_timings.dat");
    std::ofstream color_out("results/color_count.dat");
    Courses courses({"CS", "EE", "MATH", "PHYS", "CHEM", "BIO", "IE", "ME"});

    outfile << setw(20)<<"Runtime(ms)";
    color_out << setw(20)<<"Color_Count";
    for (int i = 0; i < algo_names.size(); ++i) {
        outfile << setw(20)<<algo_names[i];
        color_out << setw(20)<<algo_names[i];
    }
    outfile << std::endl;
    color_out << std::endl;
    for (int size = 16; size <= 2048; size *= 2) {
        outfile << setw(20)<<size;
        color_out << setw(20)<<size;
        Graph<type> g;
        g.create_random_graph(size, size * (size/7), random);

        for (size_t i = 0; i < algo_types.size(); ++i) {
            algorithm alg = findAlgorithm<type>(g, algo_types[i]);

            auto start = std::chrono::high_resolution_clock::now();
            (g.*alg)();
            auto end = std::chrono::high_resolution_clock::now();

            if (!g.check_coloring()) {
                std::cout <<algo_names[i]<<"   Invalid coloring!" << std::endl;
            }

            std::chrono::duration<double, std::milli> elapsed = end - start;
            
            
            color_out << setw(20)<<g.countColors();
            outfile <<setw(20)<<elapsed.count();
        }
        outfile << std::endl;
        color_out << std::endl;
    }
    outfile.close();
}