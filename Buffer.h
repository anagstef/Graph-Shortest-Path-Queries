#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <new>
#include "NodeIndex.h"
#include "list_node.h"
#define BUFFER_INIT_SIZE 20000
//#define BUFFER_INIT_SIZE 2000

class Buffer {
private:
    uint32_t length; //how many list nodes are inside the buffer
    uint32_t real_size; //the actual size of the buffer
    list_node* nodes;
public:
    Buffer();
    ~Buffer();

    uint32_t allocNewNode(); //initializes a new listnode and returns the pointer
    list_node* getListNode(uint32_t ptr); //returns a pointer to a listnode, or NULL if it does not exist
    //adds a new edge checking for duplicate. returns false if the node already exists
    bool addNewEdge(uint32_t edge_id, uint32_t listHead, NodeIndex &index);
    //adds a new edge without checking for duplicate
    void addNewEdgeDirectly(uint32_t edge_id, uint32_t nodeId, NodeIndex &index);
};


#endif
