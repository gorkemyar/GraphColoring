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
        void addEdgeUndirected(type from, type to, int weight);
        bool checkEdge(type from, type to);
        void printGraph();
        void printPath(node<type>* from, node<type>* to);
        bool isConnected();
        bool deleteNode(type word);
        bool deleteEdge(type from, type to);
        void BFS(function<type(type)> func, type from);
        void DFS(function<type(type)> func, type from);
        void create_random_graph(int num_nodes, int num_edges, function<type(type)> random_generator);
    private:
        unordered_map<type, node<type>*> map;
        vector<node<type>*> vertexes;
        unordered_set<node<type>*> visited;
        unordered_set<node<type>*> colored;

        node<type>* findNode(type from);
        
};

template <class type>
Graph<type>::Graph(){
    //cout << "Graph created" << endl;
    map.clear();
    vertexes.clear();
    visited.clear();
    colored.clear();
}

template <class type>
Graph<type>::~Graph(){
    //cout << "Graph destroyed" << endl;
    for (int i=0; i<vertexes.size(); i++){
        deleteNode(vertexes[i]->word);
    }

    map.clear();
    vertexes.clear();
    visited.clear();
    colored.clear();
}

template <class type>
node<type>* Graph<type>::findNode(type from){
    if (map.find(from) != map.end()){
        return map[from];
    }
    return nullptr;
}

template <class type>
void Graph<type>::addNode(type word){
    if (map.find(word) == map.end()){
        node<type>* n = new node<type>(word);
        map[word] = n;
        vertexes.push_back(n);
    } else{
        cout << "Node already exists" << endl;
    }
}

template <class type>
void Graph<type>::addEdgeDirected(type from, type to, int weight){
    node<type>* f = findNode(from);
    node<type>* t = findNode(to);
    if (f != nullptr && t != nullptr && f != t && !checkEdge(from, to)){
        edge<type> e(f, t, weight);
        f->adjacent.push_back(e);
    } else{
        cout << "Node does not exist" << endl;
    }
}

template <class type>
void Graph<type>::addEdgeUndirected(type from, type to, int weight){
    node<type>* f = findNode(from);
    node<type>* t = findNode(to);
    if (f != nullptr 
        && t != nullptr 
        && f != t 
        && !checkEdge(from, to) 
        && !checkEdge(to, from)){

        edge<type> e1(f, t, weight);
        edge<type> e2(t, f, weight);
        f->adjacent.push_back(e1);
        t->adjacent.push_back(e2);
    } else{
        cout << "Node does not exist" << endl;
    }
}


template <class type>
bool Graph<type>::checkEdge(type from, type to){
    node<type>* f = findNode(from);
    node<type>* t = findNode(to);
    if (f != nullptr && t != nullptr){
        for (auto it = f->adjacent.begin(); it != f->adjacent.end(); it++){
            if (it->to == t){
                return true;
            }
        }
    }
    return false;
}

template <class type>
void Graph<type>::printGraph(){
    for (int i=0; i<vertexes.size(); i++){
        cout << vertexes[i]->word << ": ";
        for (auto it = vertexes[i]->adjacent.begin(); it != vertexes[i]->adjacent.end(); it++){
            cout << it->to->word << " ";
        }
        cout << endl;
    }
}

template <class type>
void Graph<type>::printPath(node<type>* from, node<type>* to){
    if (from == to){
        cout << from->word << " ";
    } else if (to->path == nullptr){
        cout << "No path from " << from->word << " to " << to->word << " exists" << endl;
    } else{
        printPath(from, to->path);
        cout << to->word << " ";
    }
}

template <class type>
bool Graph<type>::isConnected(){
    if (vertexes.size() == 0){
        return false;
    }
    node<type>* start = vertexes[0];
    queue<node<type>*> q;
    q.push(start);
    visited.insert(start);
    while (!q.empty()){
        node<type>* n = q.front();
        q.pop();
        for (auto it = n->adjacent.begin(); it != n->adjacent.end(); it++){
            if (visited.find(it->to) == visited.end()){
                q.push(it->to);
                visited.insert(it->to);
            }
        }
    }
    if (visited.size() == vertexes.size()){
        visited.clear();
        return true;
    }
    visited.clear();
    return false;
}


// there is a dangling pointer problem here if the edge is not undirected and points to the deleted node
template <class type>
bool Graph<type>::deleteNode(type word){
    node<type>* n = findNode(word);
    if (n != nullptr){
        for (auto it = n->adjacent.begin(); it != n->adjacent.end(); it++){
            deleteEdge(n->word, it->to->word);
            if checkEdge(it->to->word, n->word){
                deleteEdge(it->to->word, n->word);
            }
        }
        map.erase(word);
        for (int i=0; i<vertexes.size(); i++){
            if (vertexes[i] == n){
                vertexes.erase(vertexes.begin()+i);
                break;
            }
        }
        delete n;
        return true;
    }
    return false;
}

template <class type>
bool Graph<type>::deleteEdge(type from, type to){
    node<type>* f = findNode(from);
    node<type>* t = findNode(to);
    if (f != nullptr && t != nullptr){
        for (auto it = f->adjacent.begin(); it != f->adjacent.end(); it++){
            if (it->to == t){
                f->adjacent.erase(it);
                return true;
            }
        }
    }
    return false;
}

template <class type>
void Graph<type>::BFS(function<type(type)> func, type start){
    node<type>* n = findNode(start);
    if (n != nullptr){
        queue<node<type>*> q;
        q.push(n);
        visited.insert(n);
        while (!q.empty()){
            node<type>* n = q.front();
            q.pop();
            for (auto it = n->adjacent.begin(); it != n->adjacent.end(); it++){
                if (visited.find(it->to) == visited.end()){
                    q.push(it->to);
                    visited.insert(it->to);
                }
            }
            func(n->word);
        }
        visited.clear();
    }
}

template <class type>
void Graph<type>::DFS(function<type(type)> func, type start){
    node<type>* n = findNode(start);
    if (n != nullptr){
        stack<node<type>*> s;
        s.push(n);
        visited.insert(n);
        while (!s.empty()){
            node<type>* n = s.top();
            s.pop();
            for (auto it = n->adjacent.begin(); it != n->adjacent.end(); it++){
                if (visited.find(it->to) == visited.end()){
                    s.push(it->to);
                    visited.insert(it->to);
                }
            }
            func(n->word);
        }
        visited.clear();
    }
}

template <class type>
void Graph<type>::create_random_graph(int num_nodes, int num_edges, function<type(type)> random_generator){
    
    for (int i=0; i<num_nodes; i++){
        type obj = random_generator(i);
        while (findNode(obj) != nullptr){
            obj = random_generator(i);
        }
        addNode(obj);
    }

    num_edges = max(num_edges, num_nodes-1)
    for (int i=1; i<num_nodes; i++){
        int from = rand()%i;
        int to = rand()%num_nodes;
        int weight = rand()%100;
        addEdgeUndirected(vertexes[from]->word, vertexes[to]->word, weight);
    }
}



#endif