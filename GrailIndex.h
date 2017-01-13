#ifndef GRAILINDEX_H
#define GRAILINDEX_H

#include <cstdint>
#include <cstdlib>
#include <time.h>
#include "Graph.h"
#include "Stack.h"

struct grailNode {
    uint32_t nodeID;
    uint32_t rank;
    uint32_t minrank;
    uint32_t iterator;
    uint32_t numOfNeighbors;
    uint32_t* neighbors;
};

class GrailIndex {
private:
    NodeIndex* HyperIndex;
    Buffer* HyperBuf;
    grailNode* grail;
    Stack<uint32_t>* stack;
    uint32_t rank;
    uint32_t grail_size;
    uint32_t* invertedIndex;
public:
    GrailIndex(NodeIndex& HyperIndex, Buffer& HyperBuf);
    ~GrailIndex();

    bool askGrail(uint32_t X, uint32_t Y);
    void GrailDFS(uint32_t current);
    uint32_t* createHyperNeighborsArray(uint32_t nodeId);
};


#endif
