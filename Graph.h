#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <new>
#include "Buffer.h"
#include "NodeIndex.h"
#include "Queue_.h"
//#include "HT_Template.h"
//#include "Queue.h"
//#include "HashTable.h"
#include "Explored.h"

//struct ConectedComponents {
//    uint32_t component_id;
//    uint32_t included_nodes_count;
//    uint32_t* included_nodes_ids;
//};

class Graph {
private:
    NodeIndex In; //index for incoming edges
    NodeIndex Out;//index for outcoming edges
    Buffer In_Buf;//buffer for incoming edges
    Buffer Out_Buf;//buffer for outcoming edges
    Queue<uint32_t> ForwardFringe;
    Queue<uint32_t> BackwardsFringe;
    Explored ForwardExplored;
    Explored BackwardsExplored;
    //ConectedComponents* components;
public:
    void add(uint32_t from, uint32_t to); //add a new edge
    int query(uint32_t from, uint32_t to); //search for the shortest path and return it
    void printGraph(); //unit testing
    void clean();
    NodeIndex getIn() {return In;}
    NodeIndex getOut() {return Out;}
};

#endif
