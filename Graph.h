#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <new>
#include "Buffer.h"
#include "NodeIndex.h"
#include "Queue_.h"
#include "HashTable.h"

class Graph{
private:
    NodeIndex In; //index for incoming edges
    NodeIndex Out;//index for outcoming edges
    Buffer In_Buf;//buffer for incoming edges
    Buffer Out_Buf;//buffer for outcoming edges
public:
    //Queue<uint32_t> ForwardFringe;
    //Queue<uint32_t> BackwardsFringe;
    void add(uint32_t from, uint32_t to); //add a new edge
    int query(uint32_t from, uint32_t to); //search for the shortest path and return it
    void printGraph(); //unit testing
};

#endif
