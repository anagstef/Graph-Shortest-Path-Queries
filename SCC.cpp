#include "SCC.h"

SCC::SCC() {
    comps_size = COMPONENTS;
    components = (Component*) malloc(comps_size * sizeof(Component));
    components_count = 0;
    id_belongs_to_component = (uint32_t*) malloc(comps_size * sizeof(uint32_t));
}

SCC::~SCC() {
    free(components);
    free(id_belongs_to_component);
}

void SCC::estimateStronglyConnectedComponents(Graph graph) {
    uint32_t index = 0;
    uint32_t graphNodes = graph.getIn().getSize();
    if (graphNodes < graph.getOut().getSize()) graphNodes = graph.getOut().getSize();
    bool onStack = new bool[graphNodes];
    Node* nodes = (Node*) malloc(graphNodes*sizeof(Node));
    for (uint32_t i = 0; i < graphNodes; i++) {
        nodes[i].index = 0;
    }
    for (uint32_t i = 0; i < graphNodes; i++) {
        if (nodes[i].index == 0) {
            tarjan(&nodes[i], index, &onStack);
        }
        stack.clear();
    }
}

void SCC::tarjan(Node *node, uint32_t &index, bool* onStack) {
    
}
