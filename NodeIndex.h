#ifndef NODEINDEX_H
#define NODEINDEX_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <new>
#define INDEX_INIT_SIZE 500

class NodeIndex{
private:
    uint32_t* Index;
    bool* IndexedNodes;
    uint32_t size;
public:
    NodeIndex();
    ~NodeIndex();

    uint32_t getListHead(uint32_t nodeId);
    bool insertNode(uint32_t nodeId, uint32_t buffer_offset);
    bool isIndexed(uint32_t nodeId);
};

#endif
