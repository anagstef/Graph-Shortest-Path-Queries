#ifndef NODEINDEX_H
#define NODEINDEX_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <new>
#define INDEX_INIT_SIZE 150000

typedef struct {
  uint32_t listHead; //pointer to the starting listnode of its neighbors
  uint32_t listTail; //pointer to the last listnode, for efficiency
  bool indexed; //true if the node exists, false otherwise
  uint32_t numOfNeighbors; //number of neighbors the node has
  uint32_t minVersion;
}iNode;

class NodeIndex{
private:
    iNode* Index;
    uint32_t size; //the actual size of the NodeIndex
    uint32_t numOfNodes; //number of the nodes that are indexed on this index
public:
    NodeIndex();
    ~NodeIndex();

    uint32_t getListHead(uint32_t nodeId);
    uint32_t getListTail(uint32_t nodeId);
    uint32_t getNumOfNeighbors(uint32_t nodeId);
    bool existsInThisVersion(uint32_t nodeId, uint32_t version);
    uint32_t getSize() {return size;}
    uint32_t getNumOfNodes() {return numOfNodes;}
    void addNeighbor(uint32_t nodeId){ (Index[nodeId].numOfNeighbors)++; }
    void setListTail(uint32_t nodeId, uint32_t tail);
    bool insertNode(uint32_t nodeId, uint32_t buffer_offset, uint32_t minVersion);
    bool isIndexed(uint32_t nodeId);
};

#endif
