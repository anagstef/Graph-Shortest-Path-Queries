#ifndef SCC_H
#define SCC_H

#include <cstdint>
#include <cstdlib>
#include "Graph.h"
#include "Stack.h"

#define COMPONENTS 100    //Component* components (how many components the graph has)
                         //Same size with id_belongs_to_component, parallel matrix
#define NODES 100         //Included_nodes_ids (for every component, the nodes it has)

struct Node {
    uint32_t id;
    uint32_t index;
    uint32_t lowlink;
    int vindex;
    Node* prevNode;
    Queue<Node> nodes;
};

struct Component {
    uint32_t component_id;
    uint32_t included_nodes_count;
    uint32_t* included_nodes_ids;
};

class SCC {
private:
    Component* components;
    uint32_t  components_count;
    uint32_t* id_belongs_to_component;
    uint32_t  comps_size;
public:
    SCC(Graph graph);
    ~SCC();
    void addComponent(Component *component);
    void estimateStronglyConnectedComponents(Graph graph);
    Component* tarjan(Node *node, uint32_t &index, uint32_t** onStack, Stack<uint32_t> stack);
};

#endif
