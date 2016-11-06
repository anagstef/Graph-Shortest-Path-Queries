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

bool Buffer::addNewEdge(uint32_t edge_id, uint32_t listHead) {
    int len, i;
    uint32_t new_listnode_id;

    while(1){ //loop until the edge is found or you reach the end
        len = nodes[listHead].get_length();

        for(i=0; i<len; i++){ //for every node in a list_node
            if (nodes[listHead].get_neighbor(i) == edge_id){
                return false;
            }
        }

        if(nodes[listHead].get_hasNext()){ //get the next list_node
            listHead = nodes[listHead].get_nextNode();
        }
        else{ //break loop if there are no more listnodes
            break;
        }
    }

    len = nodes[listHead].get_length();

    if(len < N){ //if the capacity is not full add it
        nodes[listHead].set_neighbor(len, edge_id);
        nodes[listHead].set_length(len + 1);
        return true;
    }
    else{ //else, alloc a new listnode and then add the edge
        new_listnode_id = allocNewNode();
        nodes[listHead].set_nextNode(new_listnode_id);
        nodes[listHead].set_hasNext(true);

        nodes[new_listnode_id].set_neighbor(0, edge_id);
        nodes[new_listnode_id].set_length(1);
        return true;
    }

}