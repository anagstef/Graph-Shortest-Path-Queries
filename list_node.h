//
// Created by helena on 4/11/2016.
//

#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <iostream>
#define N 100

class list_node {
private:
    int node_id;
    int* neighbor;
    int* edgeProperty;
    int nextNode;
public:
    list_node(int id);
    ~list_node();
    int get_id() { return  node_id; }
    int get_nextNode() { return nextNode; }
    int* get_neighbor() { return  neighbor; }
    int* get_edgeProperty() { return edgeProperty; }
    void print_node();
};

#endif
