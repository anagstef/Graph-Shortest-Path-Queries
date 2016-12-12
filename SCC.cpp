#include "SCC.h"

SCC::SCC(Graph graph) {
    comps_size = COMPONENTS;
    components = (Component*) malloc (comps_size * sizeof(Component));
    components_count = 0;
    uint32_t graphNodes;
    if (graph.getIn().getSize() < graph.getOut().getSize()) graphNodes = graph.getOut().getSize();
    else graphNodes = graph.getIn().getSize();
    id_belongs_to_component = (uint32_t*) malloc (graphNodes * sizeof(uint32_t));
}

SCC::~SCC() {
    free(components);
    free(id_belongs_to_component);
}

void SCC::addComponent(Component *component) {
    if (components_count == comps_size) {
        comps_size = comps_size*2;
        components = (Component*) realloc (components, comps_size * sizeof(Component));
    }
    components[components_count] = *component;
    components_count++;
    for (uint32_t i = 0; i < component->included_nodes_count; ++i) {
        id_belongs_to_component[component->included_nodes_ids[i]] = component->component_id;
    }
}

void SCC::estimateStronglyConnectedComponents(Graph graph) {
    SCC components(graph);
    uint32_t graphNodes;
    if (graph.getIn().getSize() < graph.getOut().getSize()) graphNodes = graph.getOut().getSize();
    else graphNodes = graph.getIn().getSize();

    int* onStack = (int*) calloc(graphNodes, sizeof(int));
    Stack <uint32_t> stack;
    uint32_t index = 0;

    Node* nodes = (Node*) malloc(graphNodes*sizeof(Node));
    for (uint32_t i = 0; i < graphNodes; i++) {
        nodes[i].id = i;
        nodes[i].index = 0;
    }
    for (uint32_t i = 0; i < graphNodes; i++) {
        if (nodes[i].index == 0) {
            Component* tempComponent = tarjan(&nodes[i], index, &onStack, stack);
            components.addComponent(tempComponent);
        }
        stack.clear();
    }
}

Component* SCC::tarjan(Node *node, uint32_t &index, uint32_t** onStack, Stack<uint32_t> stack) {

    return NULL;
}