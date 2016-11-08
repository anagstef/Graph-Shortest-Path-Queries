#ifndef NODEINDEX_H
#define NODEINDEX_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <new>
#define INDEX_INIT_SIZE 2

typedef struct {
  uint32_t listHead;
  uint32_t listTail;
  bool indexed;
  uint32_t numOfNeighbors;
}iNode;

class NodeIndex{
private:
    // uint32_t* Index;
    // bool* IndexedNodes;
    iNode* Index;
    uint32_t size;
public:
    NodeIndex();
    ~NodeIndex();

    uint32_t getListHead(uint32_t nodeId);
    uint32_t getListTail(uint32_t nodeId);
    uint32_t getNumOfNeighbors(uint32_t nodeId);
    uint32_t getSize() {return size;}
    void addNeighbor(uint32_t nodeId){ (Index[nodeId].numOfNeighbors)++; }
    void setListTail(uint32_t nodeId, uint32_t tail);
    bool insertNode(uint32_t nodeId, uint32_t buffer_offset);
    bool isIndexed(uint32_t nodeId);
};

#endif
