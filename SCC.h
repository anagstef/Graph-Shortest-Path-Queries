#ifndef SCC_H
#define SCC_H

#include <cstdint>
#include <cstdlib>
#include "Graph.h"
#include "GrailIndex.h"
#include "Templates.h"

#define SCC_STACK_INIT_SIZE 1000
#define COMPONENTS 100    //Component* components (how many components the graph has)
                          //Same size with id_belongs_to_component, parallel matrix
#define NODES 100         //Included_nodes_ids (for every component, the nodes it has)

class GrailIndex;

struct Node {           //needed for tarjan
    uint32_t index;
    uint32_t lowlink;
    uint32_t iterator;
    uint32_t prevNode;
    uint32_t numOfNeighbors;
    uint32_t* neighbors;
};

struct Component {
    uint32_t component_id;
    uint32_t included_nodes_count;
    uint32_t* included_nodes_ids;
};

struct ComponentCursor {
    Component* component_ptr;
    uint32_t offset;
    uint32_t max_offset;
};

class SCC {
private:
    NodeIndex* In;
    NodeIndex* Out;
    Buffer* In_Buf;
    Buffer* Out_Buf;
    NodeIndex* HyperIndex;
    Buffer* HyperBuf;
    Component* components;
    ComponentCursor* cursor;
    uint32_t  components_count;
    uint32_t* id_belongs_to_component;
    uint32_t  comps_size;
    GrailIndex* grailindex;
public:
    SCC(NodeIndex& In, NodeIndex& Out, Buffer& In_Buf, Buffer& Out_Buf);
    ~SCC();
    void addComponent(Component *component);
    void estimateStronglyConnectedComponents();
    void tarjan(uint32_t nodeID, uint32_t &index, Stack<uint32_t> &stack, Node* nodesArray, int* onStack);
    void printComponents();
    bool iterateStronglyConnectedComponentID();
    uint32_t* createNeighborsArrayFromOut(uint32_t nodeId);
    uint32_t* getIDbtc() { return id_belongs_to_component; }
    Node* tarjanInit(uint32_t numOfNodes);
    Component* getComponents() { return components; }
    ComponentCursor* cursorInit();
    bool next_StronglyConnectedComponentID(ComponentCursor* cursor);
    uint32_t getComponentsCount() { return components_count; }
    void createHyperGraph();
    bool nodesBelongToSameSCC(uint32_t node1, uint32_t node2);
    bool nodeBelongsToSCC(uint32_t node, uint32_t component_id);
    uint32_t findNodeStronglyConnectedComponentID(uint32_t nodeId);
    int querySCC(uint32_t node1, uint32_t node2);
};

#endif
