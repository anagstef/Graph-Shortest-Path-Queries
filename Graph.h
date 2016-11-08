#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <new>
#include "Buffer.h"
#include "NodeIndex.h"

class Graph{
private:
    NodeIndex In;
    NodeIndex Out;
    Buffer In_Buf;
    Buffer Out_Buf;
public:
    void add(uint32_t from, uint32_t to);
    int query(uint32_t from, uint32_t to);
};

#endif
