#include "SCC.h"

SCC::SCC(NodeIndex& In, NodeIndex& Out, Buffer& In_Buf, Buffer& Out_Buf) {
    this->In = &In;
    this->Out = &Out;
    this->In_Buf = &In_Buf;
    this->Out_Buf = &Out_Buf;
    comps_size = COMPONENTS;
    components = (Component*) malloc (comps_size * sizeof(Component));
    components_count = 0;
    uint32_t graphNodes;
    if (In.getSize() < Out.getSize()) graphNodes = Out.getSize();
    else graphNodes = In.getSize();
    id_belongs_to_component = (uint32_t*) malloc (graphNodes * sizeof(uint32_t));
    estimateStronglyConnectedComponents();
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

void SCC::estimateStronglyConnectedComponents() {
    uint32_t graphNodes;

    if (In->getSize() < Out->getSize()) graphNodes = Out->getSize();
    else graphNodes = In->getSize();

    int* onStack = (int*) calloc(graphNodes, sizeof(int));
    Stack <uint32_t> stack;

    Node* nodes = (Node*) malloc(graphNodes*sizeof(Node));
    for (uint32_t i = 0; i < graphNodes; i++) {
        nodes[i].id = i;
        nodes[i].index  = 0;
        nodes[i].vindex = 0;
        nodes[i].nodes  = In->getNumOfNeighbors(i);
        list_node* current;
        current = Out_Buf->getListNode(Out->getListHead(i));
        nodes[i].neighbors = current->get_neighborArray();
    }
    uint32_t index = 0;
    for (uint32_t i = 0; i < graphNodes; i++) {
        if (nodes[i].index == 0) {
            tarjan(&nodes[i], index, onStack, stack, &nodes);
            stack.clear();
        }
    }
}



void SCC::tarjan(Node *node, uint32_t &index, int* onStack, Stack<uint32_t> stack, Node** nodesArray) {
    Component *component = NULL;
    node->index = index;
    node->lowlink = index;
    node->vindex = 0;
    node->prevNode = NULL;

    index++;
    stack.push(node->id);
    onStack[node->id] = 1;
    Node* lastVisited = node;
    while (1) {
        if (lastVisited->vindex < lastVisited->nodes) {
            uint32_t neighbor = lastVisited->neighbors[lastVisited->vindex];
            Node *w = nodesArray[neighbor];
            lastVisited->vindex++;
            if (w->index == 0) {
                w->index = index;
                w->lowlink = index;
                w->vindex = 0;
                w->prevNode = lastVisited;
                index++;
                stack.push(w->id);
                onStack[w->id] = 1;
                lastVisited = w;
            }
            else if (onStack[w->id] == 1) {
                if (lastVisited->lowlink > w->index)
                    lastVisited->lowlink = w->index;
            }
        }
        else {
            if (lastVisited->lowlink == lastVisited->index) {
                uint32_t compSize = stack.getSize();
                components_count++;
                component->component_id = components_count;
                component->included_nodes_count = compSize;
                component->included_nodes_ids = (uint32_t*) malloc(compSize * sizeof(uint32_t));
                for (uint32_t i = 0; i < compSize; ++i) {
                    if (!stack.isEmpty()) {
                        component->included_nodes_ids[i] = stack.pop();
                        onStack[component->included_nodes_ids[i]] = 0;

                    }
                    else
                        break;
                }
                addComponent(component);
            }
            Node *newLast = lastVisited->prevNode;
            if (newLast != NULL) {
                if (newLast->lowlink > lastVisited->lowlink)
                    newLast->lowlink = lastVisited->lowlink;
                lastVisited = newLast;
            }
            else {
                break;
            }
        }
    }
}
