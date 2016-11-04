//
// Created by helena on 4/11/2016.
//

#include "list_node.h"

using namespace std;

list_node::list_node(int id) {
    int i;
    neighbor = new int[N];
    edgeProperty = new int[N];
    for (i = 0; i < N; ++i) {
        neighbor[i] = -1;
        edgeProperty[i] = -1;
    }
    node_id = id;
    nextNode = -1;
}

list_node::~list_node() {
    delete[] neighbor;
    delete[] edgeProperty;
}

void list_node::print_node() {
    int i;
    cout << "Node id: " << node_id << endl;
    cout << "Neigbors: " << endl;
    for (i = 0; i < N; ++i) {
        cout << i << " " << neighbor[i] << endl;
    }
    cout << "Edges: " << endl;
    for (i = 0; i < N; ++i) {
        cout << i << " " << edgeProperty[i] << endl;
    }
    cout << "Next: " << nextNode << endl;
}
