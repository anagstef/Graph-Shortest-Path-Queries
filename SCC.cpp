#include "SCC.h"

using namespace std;

SCC::SCC(NodeIndex& In, NodeIndex& Out, Buffer& In_Buf, Buffer& Out_Buf) {
    this->In = &In;
    this->Out = &Out;
    this->In_Buf = &In_Buf;
    this->Out_Buf = &Out_Buf;
    comps_size = COMPONENTS;
    components = (Component*) malloc (comps_size * sizeof(Component));
    components_count = 0;
    uint32_t graphNodes;
    if (In.getNumOfNodes() < Out.getNumOfNodes())
        graphNodes = Out.getNumOfNodes();
    else
        graphNodes = In.getNumOfNodes();
    id_belongs_to_component = (uint32_t*) malloc (graphNodes * sizeof(uint32_t));
    Stack<uint32_t> *stack = new Stack<uint32_t>();
    estimateStronglyConnectedComponents(stack);
    cout << "Components Count: " << components_count << endl;
    printComponents();
}

SCC::~SCC() {
    free(components);
    free(id_belongs_to_component);
}

void SCC::printComponents() {
    for (uint32_t i = 0; i < components_count; i++) {
        cout << "Component " << components[i].component_id << endl;
        for (uint32_t j = 0; j < components[i].included_nodes_count; j++) {
            printf("%u, ", components[i].included_nodes_ids[j]);
        }
        cout <<  endl;
    }
}

void SCC::addComponent(Component *component) {
    if (components_count == comps_size) {
        comps_size = comps_size*2;
        components = (Component*) realloc (components, comps_size * sizeof(Component));
    }
    component->component_id = components_count + 1;
    components[components_count] = *component;
    components_count++;
    for (uint32_t i = 0; i < component->included_nodes_count; ++i) {
        id_belongs_to_component[component->included_nodes_ids[i]] = component->component_id;
    }
}

Node* SCC::tarjanInit(uint32_t numOfNodes) {
    Node* nodes = (Node*) malloc(sizeof(Node) * numOfNodes);
    list_node* current;
    for (uint32_t i = 0; i < numOfNodes; i++) {
        if (Out->isIndexed(i)) {
            nodes[i].index  = UINT32_MAX;
            nodes[i].lowlink = 0;
            nodes[i].vindex = UINT32_MAX;
            nodes[i].numOfNeighbors = Out->getNumOfNeighbors(i);
            current = Out_Buf->getListNode(Out->getListHead(i));
            nodes[i].neighbors = current->get_neighborArray();
        }
        else {
            nodes[i].numOfNeighbors = -1;
        }
    }
    return nodes;
}

void SCC::estimateStronglyConnectedComponents(Stack<uint32_t> *stack) {
    uint32_t graphNodes = Out->getSize();
    int* onStack = (int*) calloc(graphNodes, sizeof(int));
    Node* nodes = tarjanInit(graphNodes);
    uint32_t index = 0;
    for (uint32_t i = 0; i < graphNodes; i++) {
        if (Out->isIndexed(i)) {
            if (nodes[i].index == UINT32_MAX) {
                tarjan(i, index, stack, nodes, onStack);
                stack->clear();
                cout << "Finished with -- " << i << " -- " << index << endl;
                cout << endl;
            }
        }
    }
}

void SCC::tarjan(uint32_t nodeID, uint32_t &index, Stack<uint32_t> *stack, Node* nodes, int* onStack) {
    uint32_t last, w, newLast;
    nodes[nodeID].index = index;
    nodes[nodeID].lowlink = index;
    nodes[nodeID].vindex = 0;
    nodes[nodeID].prevNode = UINT32_MAX;
    index++;
    stack->push(nodeID);
    onStack[nodeID] = 1;
    last = nodeID;
    while (1) {
        if (nodes[last].vindex < nodes[last].numOfNeighbors) {
            w = nodes[last].neighbors[nodes[last].vindex];
            nodes[last].vindex++;
            if (Out->isIndexed(w) && nodes[w].index == UINT32_MAX) {
                nodes[w].prevNode = last;
                nodes[w].vindex = 0;
                nodes[w].index = index;
                nodes[w].lowlink = index;
                index++;
                stack->push(w);
                onStack[w] = 1;
                last = w;
            }
            else if (onStack[w] == 1) {
                if (nodes[last].lowlink < nodes[w].index)
                    nodes[last].lowlink = nodes[last].lowlink;
                else
                    nodes[last].lowlink = nodes[w].index;
            }
        }
        else {
            if (nodes[last].lowlink == nodes[last].index) {
                cout << "Component found" << endl;
                cout << "Stack size " << stack->getSize() << endl;
                uint32_t compSize = stack->getSize();
                uint32_t* tempArray = (uint32_t*) malloc(compSize*sizeof(uint32_t));
                uint32_t offset = 0;
                uint32_t id = stack->pop();
                onStack[id] = 0;
                tempArray[offset] = id;
                offset++;
                while (id != last) {
                    id = stack->pop();
                    onStack[id] = 0;
                    tempArray[offset] = id;
                    offset++;
                }
                Component cmp;
                cmp.included_nodes_count = offset;
                cmp.included_nodes_ids = (uint32_t*) malloc((offset)*sizeof(uint32_t));
                for (uint32_t i = 0; i < offset; i++) {
                    cout << tempArray[i] << endl;
                    cmp.included_nodes_ids[i] = tempArray[i];
                }
                free(tempArray);
                addComponent(&cmp);
            }
            newLast = nodes[last].prevNode;
            if (newLast != UINT32_MAX) {
                if (nodes[newLast].lowlink < nodes[last].lowlink)
                    nodes[newLast].lowlink = nodes[newLast].lowlink;
                else
                    nodes[newLast].lowlink = nodes[last].lowlink;
                last = newLast;
            }
            else
                break;
        }
    }
}
