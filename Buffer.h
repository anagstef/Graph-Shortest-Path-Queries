#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <new>
#include "list_node.h"
#define BUFFER_INIT_SIZE 100

class Buffer {
private:
    uint32_t length;
    uint32_t real_size;
    list_node* nodes;
public:
    Buffer();
    ~Buffer();

    uint32_t allocNewNode();
    list_node* getListNode(uint32_t ptr);
};


#endif
