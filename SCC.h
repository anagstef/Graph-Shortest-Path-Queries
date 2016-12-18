#ifndef SCC_H
#define SCC_H

#include <cstdint>
#include <cstdlib>
#include "Graph.h"
#include "Stack.h"
#include <stack>

#define COMPONENTS 100    //Component* components (how many components the graph has)
                          //Same size with id_belongs_to_component, parallel matrix
#define NODES 100         //Included_nodes_ids (for every component, the nodes it has)

struct Node {
    uint32_t index;
    uint32_t lowlink;
    uint32_t vindex;
    uint32_t prevNode;
    uint32_t numOfNeighbors;
    uint32_t* neighbors;
};

struct Component {
    uint32_t component_id;
    uint32_t included_nodes_count;
    uint32_t* included_nodes_ids;
};

class SCC {
private:
    NodeIndex* In;
    NodeIndex* Out;
    Buffer* In_Buf;
    Buffer* Out_Buf;
    Component* components;
    uint32_t  components_count;
    uint32_t* id_belongs_to_component;
    uint32_t  comps_size;
public:
    SCC(NodeIndex& In, NodeIndex& Out, Buffer& In_Buf, Buffer& Out_Buf);
    ~SCC();
    void addComponent(Component *component);
    void estimateStronglyConnectedComponents();
    void tarjan(uint32_t nodeID, uint32_t &index, Stack<uint32_t> &stack, Node* nodesArray, int* onStack);
    void printComponents();
    uint32_t* createNeighborsArrayFromOut(uint32_t nodeId);
    uint32_t* getIDbtc() { return id_belongs_to_component; }
    Node* tarjanInit(uint32_t numOfNodes);
};

#endif
