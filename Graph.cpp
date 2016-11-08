#include "Graph.h"

using namespace std;

void Graph::add(uint32_t from, uint32_t to) {
    uint32_t temp;
    bool NewEdgeAdded;

    uint32_t from_neighbors = Out.getNumOfNeighbors(from);
    uint32_t to_neighbors = In.getNumOfNeighbors(to);

    //if one of these has zero neighbors, then the edge does not exist
    if(from_neighbors == 0 || to_neighbors == 0) {

        if (Out.isIndexed(from)) {
            Out_Buf.addNewEdgeDirectly(to, from, Out);
        } else {
            temp = Out_Buf.allocNewNode();
            Out.insertNode(from, temp);
            Out_Buf.addNewEdgeDirectly(to, from, Out);
        }


        if (In.isIndexed(to)) {
            In_Buf.addNewEdgeDirectly(from, to, In);
        } else {
            temp = In_Buf.allocNewNode();
            In.insertNode(to, temp);
            In_Buf.addNewEdgeDirectly(from, to, In);
        }

    }

    if(from_neighbors <= to_neighbors){

        if (Out.isIndexed(from)) {
            NewEdgeAdded = Out_Buf.addNewEdge(to, from, Out);
        } else {
            temp = Out_Buf.allocNewNode();
            Out.insertNode(from, temp);
            NewEdgeAdded = Out_Buf.addNewEdge(to, from, Out);
        }

        if (NewEdgeAdded) {
            if (In.isIndexed(to)) {
                In_Buf.addNewEdgeDirectly(from, to, In);
            } else {
                temp = In_Buf.allocNewNode();
                In.insertNode(to, temp);
                In_Buf.addNewEdgeDirectly(from, to, In);
            }
        }

    }

    if(from_neighbors > to_neighbors){

        if (In.isIndexed(to)) {
            NewEdgeAdded = In_Buf.addNewEdge(from, to, In);
        } else {
            temp = In_Buf.allocNewNode();
            In.insertNode(to, temp);
            NewEdgeAdded = In_Buf.addNewEdge(from, to, In);
        }

        if (NewEdgeAdded) {
            if (Out.isIndexed(from)) {
                Out_Buf.addNewEdgeDirectly(to, from, Out);
            } else {
                temp = Out_Buf.allocNewNode();
                Out.insertNode(from, temp);
                Out_Buf.addNewEdgeDirectly(to, from, Out);
            }
        }

    }
}
