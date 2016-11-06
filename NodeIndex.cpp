#include "NodeIndex.h"

using namespace std;

NodeIndex::NodeIndex() {
    size = INDEX_INIT_SIZE;
    Index = (uint32_t*) malloc(sizeof(uint32_t) * size);
    IndexedNodes = (bool*) malloc(sizeof(bool) * size);

    for(int i=0; i<size; i++)
        IndexedNodes[i] = false;
}

NodeIndex::~NodeIndex() {
    free(IndexedNodes);
    free(Index);
}

uint32_t NodeIndex::getListHead(uint32_t nodeId) {
    return Index[nodeId];
}

bool NodeIndex::isIndexed(uint32_t nodeId) {
    if(nodeId<size)
        return IndexedNodes[nodeId];
    else
        return false;
}

bool NodeIndex::insertNode(uint32_t nodeId, uint32_t buffer_offset){
    uint32_t new_size;

    if (nodeId >= size){ //if the node has bigger value than the index

        new_size = size * 2; //double the size

        if(nodeId >= new_size){
            new_size = nodeId + 1; //or make it even bigger
        }

        //realloc the index
        Index = (uint32_t*) realloc(Index, sizeof(uint32_t) * new_size);
        IndexedNodes = (bool*) realloc(IndexedNodes, sizeof(bool) * size);

        //initialize the boolean values
        for(uint32_t i=size; i < new_size; i++)
            IndexedNodes[i] = false;

        size = new_size; //update index size
    }
    else{
        if(isIndexed(nodeId)) //in case it is already indexed, just return false
            return false;
    }


    //insert the new node
    Index[nodeId] = buffer_offset;
    IndexedNodes[nodeId] = true;

    return true;
}