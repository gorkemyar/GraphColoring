#include "graph.h"
#include <fstream>
#include <iostream>

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
        //cout<<i<<" "<<vertexes[i]->word<<endl;
        //deleteNode(vertexes[i]->word);

        delete vertexes[i];
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
bool Graph<type>::addEdgeUndirected(type from, type to, int weight){
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
        return true;
    } else{
        if (f == nullptr || t == nullptr){
            cout << "Node does not exist" << endl;
            return false;
        } else if (f == t){
            cout << "Cannot add edge to itself" << endl;
            return false;
        } 

        return false;
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
void Graph<type>::printGraphJson(){
    // open output file
    ofstream out;
    out.open("graph.json");

    out << "{" << endl;
    out << "\t\"nodes\": {" << endl;
    for (int i=0; i<vertexes.size(); i++){
        out << "\t\"" << vertexes[i]->word << "\": [";
        int size = vertexes[i]->adjacent.size();
        int j = 0;
        for (auto it = vertexes[i]->adjacent.begin(); it != vertexes[i]->adjacent.end(); it++){
            out << "\"" << it->to->word;
            if (j < size -1){
                out << "\", ";
            }else{
                out << "\"";
            }
            j++;

        }
        if (i < vertexes.size() - 1){
            out << "]," << endl;
        } else{
            out << "]" << endl;
        }
    }
    out << "\t}," << endl;

    out << "\t\"colors\": [" << endl;
    for (int i=0; i<vertexes.size(); i++){
        out << "\""<<vertexes[i]->color<<"\"";
        if (i < vertexes.size() - 1){
            out << ", ";
        }
    }
    out << "]" << endl;
    out << "}" << endl;
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
            cout<<"Is error0"<<endl;
            
            cout<<"Is error0.5"<<endl;
            deleteEdge(n->word, it->to->word);
            cout<<"Is error0.75"<<endl;
            if (checkEdge(it->to->word, n->word)){
                cout<<"Is undirected"<<endl;
                deleteEdge(it->to->word, n->word);
                cout<<"Is error1"<<endl;
            }

            
        }
        cout<<"Is error2"<<endl;
        map.erase(word);
        
        cout<<"Is error3"<<endl;
        for (int i=0; i<vertexes.size(); i++){
            if (vertexes[i] == n){
                vertexes.erase(vertexes.begin()+i);
                break;
            }
        }
        
        cout<<"Is error4"<<endl;
        delete n;
        cout<<"Is error5"<<endl;
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
                cout << "Delete edge\n";
                f->adjacent.erase(it);
                cout << "Delete edge\n";
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
void Graph<type>::create_random_graph(int num_nodes, int num_edges, function<type(int)> random_generator){ 
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
        while (!addEdgeUndirected(vertexes[from]->word, vertexes[i]->word, weight)){
            from = rand()%i;
        }
    }

    num_edges -= (num_nodes-1);
    for (int i = 0; i < num_edges; i++){
        int from = rand()%num_nodes;
        int to = rand()%num_nodes;
        int weight = rand()%100;
        while (!addEdgeUndirected(vertexes[from]->word, vertexes[to]->word, weight)){
            from = rand()%num_nodes;
            to = rand()%num_nodes;
        }
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

template <class type>    
bool Graph<type>::check_neighbours_coloring(node<type>* n, string c){
    for (auto it = n->adjacent.begin(); it != n->adjacent.end(); it++){
        if (it->to->color == c){
            return false;
        }
    }
    return true;
}

template <class type>
int Graph<type>::countColors(){
    set<string> unique_colors;
    for (auto vertex : vertexes){
        if (vertex->color != ""){
            unique_colors.insert(vertex->color);
        }
    }
    return unique_colors.size();
}

template <class type>
vector<node<type>*> Graph<type>::getVertexes() const{
    return vertexes;
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


/* Algorithms for coloring the graph */

template <class type>
void Graph<type>::greedy_coloring() {
    // Sort the nodes based on their degrees in non-increasing order
    
    sort(vertexes.begin(), vertexes.end(), [](node<type>* a, node<type>* b) {
        return a->adjacent.size() > b->adjacent.size();
    });

    // Initialize colors for all nodes to "white"
    for (auto v : vertexes) {
        v->color = "white";
    }

    // Color the first node with the first available color
    vertexes[0]->color = generate_random_color();
    colors[vertexes[0]->color] = 1;

    // Color the remaining nodes
    for (size_t i = 1; i < vertexes.size(); i++) {
        // Find the first available color that is not in the adjacent nodes
        unordered_set<string> forbiddenColors;
        for (const auto &edge : vertexes[i]->adjacent) {
            forbiddenColors.insert(edge.to->color);
        }

        // Assign the first available color
        string availableColor = "";
        for (const auto &color : colors) {
            if (forbiddenColors.find(color.first) == forbiddenColors.end()) {
                availableColor = color.first;
                break;
            }
        }

        // If no available color found, create a new one and add it to the set of colors
        if (availableColor == "") {
            availableColor = generate_random_color();
            colors[availableColor] = 1;
        }

        vertexes[i]->color = availableColor;
    }
}

// Complexity O(V^2)
template <class type>
void Graph<type>::Dsatur_coloring(){
    colors.clear();
    
    sort(vertexes.begin(), vertexes.end(), [](node<type>* a, node<type>* b) {
        return a->adjacent.size() > b->adjacent.size();
    });
    
    for (auto v : vertexes) {
        v->color = "white";
    }

    vertexes[0]->color = generate_random_color();
    colors[vertexes[0]->color] = 1;

    
    for (size_t i = 1; i < vertexes.size(); i++) {
        unordered_set<string> forbiddenColors;    
        for (const auto &edge : vertexes[i]->adjacent) {
            forbiddenColors.insert(edge.to->color);
        }

        string availableColor = "";
        int min_color_count = INT_MAX;
        for (const auto &color : colors) {
            if (forbiddenColors.find(color.first) == forbiddenColors.end()) {
                if (color.second < min_color_count){
                    min_color_count = color.second;
                    availableColor = color.first;
                }
            }
        }

        if (availableColor == "") {
            availableColor = generate_random_color();
            colors[availableColor] = 1;
        }else{
            colors[availableColor] += 1;
        }

        vertexes[i]->color = availableColor;
    }

}


// Complexity O(V^2*lambda)
template <class type>
void Graph<type>::welsh_powell_coloring() {
    // Sort the nodes based on their degrees in non-increasing order
    sort(vertexes.begin(), vertexes.end(), [](node<type>* a, node<type>* b) {
        return a->adjacent.size() > b->adjacent.size();
    });

    // Initialize colors for all nodes to "white"
    for (auto v : vertexes) {
        v->color = "white";
    }

    for (int i = 0; i < vertexes.size(); i++) {
        if (vertexes[i]->color == "white") {
            vertexes[i]->color = generate_random_color();
            colors[vertexes[i]->color] = 1;
            
            vector<int> uncolored_rmn;
            for (int j = i+1; j < vertexes.size(); j++) {
                if (vertexes[j]->color == "white") {
                    uncolored_rmn.push_back(j);
                }
            }

            for (int j = 0; j < uncolored_rmn.size(); j++) {
                if (check_neighbours_coloring(vertexes[uncolored_rmn[j]], vertexes[i]->color)) {
                    vertexes[uncolored_rmn[j]]->color = vertexes[i]->color;
                    colors[vertexes[i]->color] += 1;
                }
            }
        }
    }

}


template <class type>
void Graph<type>::SDL_coloring() {
    // Sort the nodes based on their degrees in non-decreasing order
    unordered_set<node<type>*> colored_nodes;
    priority_queue<pair<int, node<type>*>> pq;
    unordered_map<node<type>*, int> saturation;
    colors.clear();
    for (auto v : vertexes) {
        v->color = "white";
        pq.push(make_pair(v->adjacent.size(), v));
        saturation[v] = 0;
    }

    // Color the nodes in order of increasing degree
    while (!pq.empty()) {

        pair<int, node<type>*> p1 = pq.top();
        pq.pop();

        node<type>* v = p1.second;
        int degree = p1.first;
        int sat = saturation[v];

        vector<pair<int, node<type>*>> temp_vec;
        while (!pq.empty()) {
            pair<int, node<type>*> p2 = pq.top();
            if (p2.first < degree) {
                break;
            }
            pq.pop();
            temp_vec.push_back(p2);
            if (saturation[p2.second] > sat) {
                v = p2.second;
                degree = p2.first;
                sat = saturation[p2.second];
            }
        }
        for (auto p : temp_vec) {
            pq.push(p);
        }
        // Find the first available color that is not in the adjacent nodes
        unordered_set<string> forbiddenColors;
        for (const auto &edge : v->adjacent) {
            forbiddenColors.insert(edge.to->color);
        }

        // Assign the first available color
        string availableColor = "";
        for (const auto &color : colors) {
            if (forbiddenColors.find(color.first) == forbiddenColors.end()) {
                availableColor = color.first;
                break;
            }
        }

        // If no available color found, create a new one and add it to the set of colors
        if (availableColor == "") {
            availableColor = generate_random_color();
            colors[availableColor] = 1;
        }

        v->color = availableColor;

        // Update the saturation of the adjacent nodes
        for (const auto &edge : v->adjacent) {
            saturation[edge.to] += 1;
        }
    }
}

