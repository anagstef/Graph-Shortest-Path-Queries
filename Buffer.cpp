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
        return &(nodes[ptr]);
    else
        return NULL;
}

uint32_t Buffer::allocNewNode() {
    if(length == real_size) { //if the maximum length is reached
        real_size *= 2;
        nodes = (list_node*) realloc(nodes, sizeof(list_node) * real_size);
    }

    new (&nodes[length]) list_node(); //use placement new to call only the constructor
    length++;
    return length - 1;
}

void Buffer::addNewEdgeDirectly(uint32_t edge_id, uint32_t nodeId, NodeIndex &index){
    int len;
    uint32_t listTail = index.getListTail(nodeId);
    uint32_t new_listnode_id;

    len = nodes[listTail].get_length();

    if(len < N){ //if the capacity is not full add it
        nodes[listTail].set_neighbor(len, edge_id);
        nodes[listTail].set_length(len + 1);
    }
    else{ //else, alloc a new listnode and then add the edge
        new_listnode_id = allocNewNode();
        nodes[listTail].set_nextNode(new_listnode_id);
        nodes[listTail].set_hasNext(true);

        nodes[new_listnode_id].set_neighbor(0, edge_id);
        nodes[new_listnode_id].set_length(1);
        index.setListTail(nodeId, new_listnode_id);
    }

    index.addNeighbor(nodeId);
}

bool Buffer::addNewEdge(uint32_t edge_id, uint32_t nodeId, NodeIndex &index) {
    int len, i;
    uint32_t listHead = index.getListHead(nodeId);
    uint32_t new_listnode_id;
    uint32_t* neighArray;

    while(1){ //loop until the edge is found or you reach the end
        len = nodes[listHead].get_length();
        neighArray = nodes[listHead].get_neighborArray();
        for(i=0; i<len; i++){ //for every node in a list_node
            // if (nodes[listHead].get_neighbor(i) == edge_id){
            if (neighArray[i] == edge_id) {
                return false; //edge exists
            }
        }

        if(nodes[listHead].get_hasNext()){ //get the next list_node
            listHead = nodes[listHead].get_nextNode();
        }
        else{ //break loop if there are no more listnodes
            break;
        }
    }


    if(len < N){ //if the capacity is not full add it
        nodes[listHead].set_neighbor(len, edge_id);
        nodes[listHead].set_length(len + 1);
    }
    else{ //else, alloc a new listnode and then add the edge
        new_listnode_id = allocNewNode();
        nodes[listHead].set_nextNode(new_listnode_id);
        nodes[listHead].set_hasNext(true);

        nodes[new_listnode_id].set_neighbor(0, edge_id);
        nodes[new_listnode_id].set_length(1);
        index.setListTail(nodeId, new_listnode_id);
    }

    index.addNeighbor(nodeId); //++
    return true; //edge added
}
