#ifndef Graph_h
#define Graph_h

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <stdio.h>
#include <list>

using namespace std;

template <class type>
struct node{
    type word;
    list<edge> adjacent;
    string color;
    node(type w, node* n=nullptr, string c="white"): word(w), next(n), color(c) {};
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
        void addEdge(type from, type to, int weight);
        void printGraph();
        void printPath(node<type>* from, node<type>* to);
        bool isConnected();
        bool deleteNode(type word);
        bool deleteEdge(type from, type to);
        bool BFS(function<type(type)> func, type from);
        bool DFS(function<type(type)> func, type from);
    private:
        unordered_map<type, node<type>*> map;
        vector<node<type>*> vertexes;
        unordered_set<node<type>*> visited;
        unordered_set<node<type>*> colored;

        node<type>* findNode(type from);
        
};





#endif