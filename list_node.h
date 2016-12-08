#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <iostream>
#include <cstdint>
#define N 10 //the size of the static array on each list node
//#define N 400 //the size of the static array on each list node

class list_node {

private:
    int length; //size of the array
    uint32_t neighbor[N];
    uint32_t edgeProperty[N];
    bool hasNext; //true if the listnode has a next node
    uint32_t nextNode; //pointer to the next node

public:
    list_node();
    ~list_node();

    uint32_t get_nextNode() { return nextNode; }
    void set_nextNode(uint32_t next) {nextNode = next;}
    bool get_hasNext() { return hasNext; }
    void set_hasNext(bool value) { hasNext = value; }

    int get_length(){ return length; }
    void set_length(int l) {length = l;}
    uint32_t get_neighbor(int i) { return  neighbor[i]; }
    uint32_t* get_neighborArray() { return  neighbor; }
    void set_neighbor(int i, uint32_t value) {neighbor[i] = value;}
    uint32_t* get_edgeProperty() { return edgeProperty; }
    void print_node(); //unit testing
};

#endif
