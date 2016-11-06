#include "Graph.h"

using namespace std;

void Graph::add(uint32_t from, uint32_t to) {
    uint32_t temp;

    if (Out.isIndexed(from)){
        Out_Buf.addNewEdge(to, Out.getListHead(from));
    }
    else {
        temp = Out_Buf.allocNewNode();
        Out.insertNode(from, temp);
        Out_Buf.addNewEdge(to, temp);
    }

    if (In.isIndexed(to)) {
        In_Buf.addNewEdge(from, In.getListHead(to));
    }
    else {
        temp = In_Buf.allocNewNode();
        In.insertNode(to, temp);
        In_Buf.addNewEdge(from, temp);
    }
}
