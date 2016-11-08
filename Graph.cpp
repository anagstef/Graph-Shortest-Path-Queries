#include "Graph.h"

using namespace std;

void Graph::add(uint32_t from, uint32_t to) {
    uint32_t temp;
    bool NewEdgeAdded = true;

    if (Out.isIndexed(from)){
        // NewEdgeAdded = Out_Buf.addNewEdge(to, from, Out);
       Out_Buf.addNewEdgeDirectly(to, from, Out);
    }
    else {
        temp = Out_Buf.allocNewNode();
        Out.insertNode(from, temp);
        // NewEdgeAdded = Out_Buf.addNewEdge(to, from, Out);
       Out_Buf.addNewEdgeDirectly(to, from, Out);
    }

    if(NewEdgeAdded){
      if (In.isIndexed(to)) {
          In_Buf.addNewEdgeDirectly(from, to, In);
      }
      else {
          temp = In_Buf.allocNewNode();
          In.insertNode(to, temp);
          In_Buf.addNewEdgeDirectly(from, to, In);
      }
    }
}
