#include "Buffer.h"

using namespace std;

Buffer::Buffer() {
    length = 0;
    real_size = BUFFER_INIT_SIZE;
    nodes = (list_node*) malloc(sizeof(list_node) * real_size);
}

Buffer::~Buffer() {
    free(nodes);
}

list_node* Buffer::getListNode(uint32_t ptr) {
    if (ptr < length)
        return nodes[ptr];
    else
        return NULL;
}

uint32_t Buffer::allocNewNode() {
    if(length == real_size) {
        real_size *= 2;
        nodes = (list_node *) realloc(sizeof(list_node) * real_size);
    }

    new (nodes[length]) list_node();
    length++;
    return length - 1;
}