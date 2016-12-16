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
        cout << "Component " << i << endl;
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
    components[components_count] = *component;
    components_count++;
    for (uint32_t i = 0; i < component->included_nodes_count; ++i) {
        id_belongs_to_component[component->included_nodes_ids[i]] = component->component_id;
    }
}

void SCC::estimateStronglyConnectedComponents(Stack<uint32_t> *stack) {
    uint32_t graphNodes;
    if (In->getSize() < Out->getSize())
        graphNodes = Out->getSize();
    else
        graphNodes = In->getSize();

    int* onStack = (int*) calloc(graphNodes, sizeof(int));
    Node* nodes = (Node*) malloc(graphNodes * sizeof(Node));
    for (uint32_t i = 0; i < graphNodes; i++) {
        if (In->isIndexed(i) || Out->isIndexed(i)) {
            nodes[i].id = i;
            nodes[i].index  = 0;
            nodes[i].lowlink = 0;
            nodes[i].vindex = graphNodes;
            nodes[i].prevNode = UINT32_MAX;
            nodes[i].numOfNeighbors = Out->getNumOfNeighbors(i);
            list_node* current;
            current = Out_Buf->getListNode(Out->getListHead(i));
            nodes[i].neighbors = current->get_neighborArray();
        }
        else {
            nodes[i].numOfNeighbors = -1;
        }

    }
    uint32_t index = 0;
    for (uint32_t i = 0; i < graphNodes; i++) {
        if (Out->isIndexed(i)) {
            if (nodes[i].index == 0) {
                tarjan(i, index, onStack, stack, nodes);
                stack->clear();
                cout << "Finished with -- " << i << endl;
                cout << endl;
            }
        }
    }
}

void SCC::tarjan(uint32_t nodeID, uint32_t &index, int* onStack, Stack<uint32_t> *stack, Node* nodesArray) {
    nodesArray[nodeID].index = index;
    nodesArray[nodeID].lowlink = index;
    nodesArray[nodeID].vindex = 0;
    nodesArray[nodeID].prevNode = UINT32_MAX;
    index++;
    stack->push(nodeID);
    onStack[nodeID] = 1;
    uint32_t lastVisited = nodeID;
    while (1) {
        if (nodesArray[lastVisited].vindex < nodesArray[lastVisited].numOfNeighbors) {
            printf("Last vindex: %d Last nodes: %d ID: %u\n", nodesArray[lastVisited].vindex, nodesArray[lastVisited].numOfNeighbors, lastVisited);
            uint32_t neighbor = nodesArray[lastVisited].neighbors[nodesArray[lastVisited].vindex];
            printf("Neighbor of %u is %u\n", lastVisited, neighbor);//nodesArray[neighbor].id);
            //Node w = nodesArray[neighbor];
            nodesArray[lastVisited].vindex++;
            if (nodesArray[neighbor].index == 0) {
                nodesArray[neighbor].index = index;
                nodesArray[neighbor].lowlink = index;
                nodesArray[neighbor].vindex = 0;
                nodesArray[neighbor].prevNode = nodesArray[lastVisited].prevNode;
                index++;
                stack->push(neighbor);
                onStack[neighbor] = 1;
                lastVisited = neighbor;
                printf("---->Low link %d\n", nodesArray[lastVisited].lowlink);
                printf("---->Index %d\n", nodesArray[lastVisited].index);
            }
            else if (onStack[neighbor] == 1) {
                printf("LowLink is %d and index is %d\n", nodesArray[lastVisited].lowlink, nodesArray[neighbor].index);
                nodesArray[lastVisited].lowlink = (nodesArray[neighbor].lowlink < nodesArray[lastVisited].index) ? nodesArray[lastVisited].lowlink : nodesArray[neighbor].index;
                printf("----<Low link %d\n", nodesArray[lastVisited].lowlink);
                printf("----<Index %d\n", nodesArray[lastVisited].index);
            }
        }
        else {
            if (nodesArray[lastVisited].lowlink == nodesArray[lastVisited].index) {
                cout << "SCC FOUND" << endl;
                uint32_t compSize = stack->getSize();
                cout << compSize << endl;
                Component component;
                component.component_id = components_count;
                component.included_nodes_count = compSize;
                component.included_nodes_ids = (uint32_t*) malloc(compSize * sizeof(uint32_t));
                for (uint32_t i = 0; i < compSize; ++i) {
                    component.included_nodes_ids[i] = stack->pop();
                    onStack[component.included_nodes_ids[i]] = 0;
                }
                addComponent(&component);
                cout << "Component added" << endl;
            }
            uint32_t newLast = nodesArray[nodeID].prevNode;
            if (newLast != UINT32_MAX) {
                nodesArray[newLast].lowlink = (nodesArray[newLast].lowlink < nodesArray[lastVisited].lowlink) ? nodesArray[newLast].lowlink : nodesArray[lastVisited].lowlink;
                lastVisited = newLast;
            }
            else
                break;
        }
    }
}
