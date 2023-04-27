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
        bool check_coloring();
        bool check_neighbors_coloring(node<type>* n, string color);
        void print_coloring();
        string generate_random_color();
        //void color_graph_brute_force();

    private:
        unordered_map<type, node<type>*> map;
        vector<node<type>*> vertexes;
        unordered_set<node<type>*> visited;

        unordered_set<string> colors;
        node<type>* findNode(type from);
        string generate_random_color_helper();
        
};

template <class type>
Graph<type>::Graph(){
    //cout << "Graph created" << endl;
    map.clear();
    vertexes.clear();
    visited.clear();
    colors.clear();
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
    colors.clear();
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
            // if (checkEdge(it->to->word, n->word)){
            //     deleteEdge(it->to->word, n->word);
            // }
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

    num_edges = max(num_edges, num_nodes-1);
    for (int i = 1; i < num_nodes; i++){
        int from = rand()%i;
        int weight = rand()%100;
        addEdgeUndirected(vertexes[from]->word, vertexes[i]->word, weight);
    }

    num_edges -= (num_nodes-1);
    for (int i = 1; i < num_edges; i++){
        int from = rand()%num_nodes;
        int to = rand()%num_nodes;
        int weight = rand()%100;
        addEdgeUndirected(vertexes[from]->word, vertexes[to]->word, weight);
    }
}

template <class type>
bool Graph<type>::check_coloring(){
    queue<node<type>*> q;
    for (int i=0; i<vertexes.size(); i++){
        if (visited.find(vertexes[i]) == visited.end()){
            q.push(vertexes[i]);
            visited.insert(vertexes[i]);
            while (!q.empty()){
                node<type>* n = q.front();
                q.pop();
                for (auto it = n->adjacent.begin(); it != n->adjacent.end(); it++){
                    if (it->to->color == n->color){
                        return false;
                    }
                    if (visited.find(it->to) == visited.end()){
                        q.push(it->to);
                        visited.insert(it->to);
                    }
                }
            }
        }
    }
    visited.clear();
    return true;
}

template<class type>    
bool Graph<type>::check_neighbors_coloring(node<type>* n, string c){
    for (auto it = n->adjacent.begin(); it != n->adjacent.end(); it++){
        if (it->to->color == c){
            return false;
        }
    }
    return true;
}

template <class type>
void Graph<type>::print_coloring(){
    
    for (int i=0; i<vertexes.size(); i++){
        cout << vertexes[i]->color << ": ";
        for (auto it = vertexes[i]->adjacent.begin(); it != vertexes[i]->adjacent.end(); it++){
            cout << it->to->color<< " ";
        }
        cout << endl;
    }
    
}

template <class type>
string Graph<type>::generate_random_color_helper(){
    string color = "#";
    for (int i=0; i<6; i++){
        int r = rand()%16;
        if (r < 10){
            color += to_string(r);
        }
        else{
            color += (char)(r-10+'A');
        }
    }
    return color;
}

template <class type>
string Graph<type>::generate_random_color(){
    string color = generate_random_color_helper();
    while (colors.find(color) != colors.end()){
        color = generate_random_color_helper();
    }
    return color;
}

// template <class type>
// void Graph<type>::color_graph_brute_force(){
//     static int colored_nodes = 0;
//     static int min_colors = INT_MAX;
//     if (colored_nodes == vertexes.size()){
//         return;
//     }

//     for (int i=0; i<vertexes.size(); i++){
//         if (vertexes[i]->color == ""){
//             vertexes[i]->color = generate_random_color();
//             colored_nodes++;
//             if (check_coloring()){
//                 color_graph_brute_force();
//             }
//             for (int j=0; j<vertexes.size(); j++){
//                 if (i != j 
//                     && !checkEdge(vertexes[i]->word, vertexes[j]->word) 
//                     && vertexes[j]->color == ""
//                     && check_neighbors_coloring(vertexes[j], vertexes[i]->color)){
                    
//                     vertexes[j]->color = vertexes[i]->color;
//                     colored_nodes++;
//                     color_graph_brute_force();
//                 }
//             }
//         }
//     }  
// }


#endif