#ifndef Graph_h
#define Graph_h

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <stdio.h>
#include <list>
#include <set>

using namespace std;

template <class type>
struct edge;
template <class type> 
struct node{
    type word;
    list< edge<type> > adjacent;
    string color;
    node(type w, string c="white"): word(w), color(c) {};
    node<type>* path = nullptr;
};

template <class type>
struct edge{
    node<type>* from;
    node<type>* to;
    int weight;
    edge(node<type>* f=nullptr, node<type>* t=nullptr, int w=0): from(f), to(t), weight(w) {};
};

template <class type>
class Graph{
    public:
        Graph();
        ~Graph();
        void addNode(type word);
        void addEdgeDirected(type from, type to, int weight);
        bool addEdgeUndirected(type from, type to, int weight);
        bool checkEdge(type from, type to);
        void printGraph();
        void printPath(node<type>* from, node<type>* to);
        void printGraphJson();
        bool isConnected();
        bool deleteNode(type word);
        bool deleteEdge(type from, type to);
        void BFS(function<type(type)> func, type from);
        void DFS(function<type(type)> func, type from);
        void create_random_graph(int num_nodes, int num_edges, function<type(int)> random_generator);
        bool check_neighbours_coloring(node<type>* n, string color);
        bool check_coloring();
        void print_coloring();

        void greedy_coloring();
        void SDL_coloring();
        void dsatur_coloring();
        void welsh_powell_coloring();
        void rlf_coloring();
       

        int countColors();
        string generate_random_color();
        vector<node<type>*> getVertexes() const;

    private:
        unordered_map<type, node<type>*> map;
        vector<node<type>*> vertexes;
        unordered_set<node<type>*> visited;

        unordered_map<string, int> colors;
        node<type>* findNode(type from);
        string generate_random_color_helper();
        void rlf_coloring_helper(node<type>* n);
        
};
#include "graph.cpp"


#endif