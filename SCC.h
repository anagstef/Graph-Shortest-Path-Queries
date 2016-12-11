#ifndef SCC_H
#define SCC_H

#include <cstdint>
#include <cstdlib>
#include "Graph.h"
#include "Stack.h"

#define COMPONENTS 10    //Component* components (how many components the graph has)
                         //Same size with id_belongs_to_component, parallel matrix
#define NODES 10         //Included_nodes_ids (for every component, the nodes it has)

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
    SCC();
    ~SCC();
    void estimateStronglyConnectedComponents(Graph graph);
};

#endif
