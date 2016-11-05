#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <iostream>
#include <cstdint>
#define N 100

class list_node {

private:
    int length;
    uint32_t neighbor[N];
    uint32_t edgeProperty[N];
    bool hasNext;
    uint32_t nextNode;

public:
    list_node();
    ~list_node();

    uint32_t get_nextNode() { return nextNode; }
    void set_nextNode(uint32_t next) {nextNode = next;}
    bool get_hasNext() { return hasNext; }
    void set_hasNext(bool value) { hasNext = value; }

    int get_length(){ return length; }
    void set_length(int l) {length = l;}
    uint32_t* get_neighbor() { return  neighbor; }
    uint32_t* get_edgeProperty() { return edgeProperty; }
    void print_node();
};

#endif
