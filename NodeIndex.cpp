#include "NodeIndex.h"

using namespace std;

NodeIndex::NodeIndex() {
    numOfNodes = 0;
    size = INDEX_INIT_SIZE;
    Index = (iNode*) malloc(sizeof(iNode) * size);

    //initialize the values
    for (uint32_t i = 0; i < size; i++){
        Index[i].indexed = false;
        Index[i].numOfNeighbors = 0;
    }
}

NodeIndex::~NodeIndex() {
    free(Index);
}

uint32_t NodeIndex::getListHead(uint32_t nodeId) {
    if(isIndexed(nodeId))
      return Index[nodeId].listHead;
    else
      return 0;
}

uint32_t NodeIndex::getListTail(uint32_t nodeId) {
    if(isIndexed(nodeId))
      return Index[nodeId].listTail;
    else
      return 0;
}

uint32_t NodeIndex::getNumOfNeighbors(uint32_t nodeId) {
  if (nodeId < size)
    return Index[nodeId].numOfNeighbors;
  else
    return 0;
}

void NodeIndex::setListTail(uint32_t nodeId, uint32_t tail){
    Index[nodeId].listTail = tail;
}

bool NodeIndex::isIndexed(uint32_t nodeId) {
    if (nodeId < size)
        return Index[nodeId].indexed;
    else
        return false; //return false if the nodeId exceeds the size of the array
}

bool NodeIndex::insertNode(uint32_t nodeId, uint32_t buffer_offset){
    uint32_t new_size;

    if (nodeId >= size) { //if the node has bigger value than the index

        new_size = size * 2; //double the size
        if (nodeId >= new_size) {
            new_size = nodeId + 1; //or make it even bigger
        }

        //realloc the index
        Index = (iNode*) realloc(Index, sizeof(iNode) * new_size);
        //initialize the boolean values
        for (uint32_t i = size; i < new_size; i++) {
            // IndexedNodes[i] = false;
            Index[i].indexed = false;
            Index[i].numOfNeighbors = 0;
        }
        size = new_size; //update index size
    }
    else {
        if (isIndexed(nodeId)) //in case it is already indexed, just return false
            return false;
    }

    //insert the new node
    Index[nodeId].listHead = buffer_offset;
    Index[nodeId].listTail = buffer_offset;
    Index[nodeId].indexed = true;
    numOfNodes++;

    return true;
}
