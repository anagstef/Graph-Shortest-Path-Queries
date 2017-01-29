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
    if (In.getSize() < Out.getSize())
        graphNodes = Out.getSize();
    else
        graphNodes = In.getSize();
    id_belongs_to_component = (uint32_t*) malloc (graphNodes * sizeof(uint32_t));
    estimateStronglyConnectedComponents();
    createHyperGraph();
    // cout << "Components Count: " << components_count << endl;
    cursor = cursorInit();
    // printComponents();
    grailindex = new GrailIndex(*HyperIndex, *HyperBuf);
}

SCC::~SCC() {
    for (uint32_t i = 0; i < components_count; i++) {
        free(components[i].included_nodes_ids);
    }
    free(components);
    free(id_belongs_to_component);
    free(cursor);
    delete HyperIndex;
    delete HyperBuf;
    delete grailindex;
}

uint32_t SCC::findNodeStronglyConnectedComponentID(uint32_t nodeId) {
    return id_belongs_to_component[nodeId];         //direct access to the array
}

//returns 1 if "Yes", 0 if "Maybe", -1 if "No"
int SCC::querySCC(uint32_t node1, uint32_t node2){
    if(id_belongs_to_component[node1] == id_belongs_to_component[node2])
      return 1;
    else{
      if(grailindex->askGrail(id_belongs_to_component[node1], id_belongs_to_component[node2]))
        return 0;
      else
        return -1;
    }
}

bool SCC::nodesBelongToSameSCC(uint32_t node1, uint32_t node2) {
    if (findNodeStronglyConnectedComponentID(node1) == findNodeStronglyConnectedComponentID(node2))
        return true;
    return false;
}

bool SCC::nodeBelongsToSCC(uint32_t node, uint32_t component_id) {
    if (id_belongs_to_component[node] != component_id)
        return false;
    return true;
}

ComponentCursor* SCC::cursorInit() {
    ComponentCursor* cursor = (ComponentCursor*) malloc(sizeof(ComponentCursor));
    cursor->offset = 0;
    cursor->max_offset = getComponentsCount();
    Component* tempArray = getComponents();
    cursor->component_ptr = &tempArray[cursor->offset];
    return cursor;
}

bool SCC::next_StronglyConnectedComponentID(ComponentCursor* cursor) {
    if (cursor->offset < cursor->max_offset) {
        cursor->offset++;
        Component* tempArray = getComponents();
        cursor->component_ptr = &tempArray[cursor->offset];
        return false;
    }
    else {
        return true;
    }
}

void SCC::printComponents() {
    int k = 0;
    for (uint32_t i = 0; i < components_count; i++) {
        if (components[i].included_nodes_count > 1) {
            k++;
            cout << "Component " << components[i].component_id << endl;
            for (uint32_t j = 0; j < components[i].included_nodes_count; j++) {
                printf("%u, ", components[i].included_nodes_ids[j]);
            }
            cout <<  endl;
        }
    }
    cout << "With 2+ nodes: " << k << endl;
}

void SCC::addComponent(Component *component) {
    if (components_count == comps_size) {   //need more components
        comps_size = comps_size*2;
        components = (Component*) realloc (components, comps_size * sizeof(Component));
    }
    component->component_id = components_count;
    components[components_count] = *component; //set the new component
    components_count++;
    for (uint32_t i = 0; i < component->included_nodes_count; ++i) { //update the array (where each node belongs)
        id_belongs_to_component[component->included_nodes_ids[i]] = component->component_id;
    }
}

uint32_t* SCC::createNeighborsArrayFromOut(uint32_t nodeId) {
      list_node* current;
      uint32_t* neighArray;
      uint32_t len;
      uint32_t* retValue;
      uint32_t iterator = 0;

      retValue = (uint32_t*) malloc(sizeof(uint32_t) * Out->getNumOfNeighbors(nodeId));
      //get current list node
      current = Out_Buf->getListNode(Out->getListHead(nodeId));

      while(1) { //loop for all neighbors
          len = current->get_length();
          neighArray = current->get_neighborArray();
          for (uint32_t j = 0; j < len; j++) { //for every node in a list_node
            retValue[iterator] = neighArray[j];
            iterator++;
          }

          if(current->get_hasNext()) { //get the next list_node
              current = Out_Buf->getListNode(current->get_nextNode());
          }
          else { //break loop if there are no more listnodes
              return retValue;
          }
    }
}

Node* SCC::tarjanInit(uint32_t numOfNodes) {                    //initialize the nodes with the right values
    Node* nodes = (Node*) malloc(sizeof(Node) * numOfNodes);
    for (uint32_t i = 0; i < numOfNodes; i++) {
        if (Out->isIndexed(i)) {
            nodes[i].index  = UINT32_MAX;
            nodes[i].lowlink = 0;
            nodes[i].iterator = UINT32_MAX;
            nodes[i].numOfNeighbors = Out->getNumOfNeighbors(i);
            nodes[i].neighbors = createNeighborsArrayFromOut(i);    //gets all the neighbors of the node
        }
        else if (In->isIndexed(i)){
            nodes[i].index  = UINT32_MAX;
            nodes[i].lowlink = 0;
            nodes[i].iterator = UINT32_MAX;
            nodes[i].numOfNeighbors = 0;
        }
    }
    return nodes;
}

void SCC::estimateStronglyConnectedComponents() {
    Stack <uint32_t> stack{SCC_STACK_INIT_SIZE};
    uint32_t graphNodes = Out->getSize();
    int* onStack = (int*) calloc(graphNodes, sizeof(int));
    Node* nodes = tarjanInit(graphNodes);
    uint32_t index = 0;
    for (uint32_t i = 0; i < graphNodes; i++) {         //for every node
        if (Out->isIndexed(i) || In->isIndexed(i)) {    //if is indexed
            if (nodes[i].index == UINT32_MAX) {         //if the index hasn't changed0
                tarjan(i, index, stack, nodes, onStack);//run tarjan
                stack.clear();
            }
        }
    }
    for (uint32_t i = 0; i < graphNodes; ++i) {
        if (Out->isIndexed(i)) {
            free(nodes[i].neighbors);
        }
    }
    free(nodes);
    free(onStack);
}

void SCC::tarjan(uint32_t nodeID, uint32_t &index, Stack<uint32_t> &stack, Node* nodes, int* onStack) {
    uint32_t last, w, newLast;
    nodes[nodeID].index = index;            //edit the node
    nodes[nodeID].lowlink = index;
    nodes[nodeID].iterator = 0;
    nodes[nodeID].prevNode = UINT32_MAX;
    index++;
    stack.push(nodeID);
    onStack[nodeID] = 1;
    last = nodeID;
    while (1) {
        if (nodes[last].iterator < nodes[last].numOfNeighbors) { //check the neighbors
            w = nodes[last].neighbors[nodes[last].iterator];     //get the first or the nth, depending on the depth
            nodes[last].iterator++;                                //increase the depth of the last node
            if ((Out->isIndexed(w) || In->isIndexed(w)) && nodes[w].index == UINT32_MAX) {
                nodes[w].prevNode = last;   //update the node
                nodes[w].iterator = 0;
                nodes[w].index = index;
                nodes[w].lowlink = index;
                index++;
                stack.push(w);
                onStack[w] = 1;
                last = w;
            }
            else if (onStack[w] == 1) { //if the node is already visited
                if (nodes[last].lowlink < nodes[w].index) //swap the lowlink with the index, we need as lowlink the smallest
                    nodes[last].lowlink = nodes[last].lowlink;
                else
                    nodes[last].lowlink = nodes[w].index;
            }
        }
        else {
            if (nodes[last].lowlink == nodes[last].index) {
                //cout << "Component found" << endl;
                uint32_t compSize = stack.getSize();
                uint32_t* tempArray = (uint32_t*) malloc(compSize*sizeof(uint32_t));
                uint32_t offset = 0;
                uint32_t id = stack.pop();
                onStack[id] = 0;
                tempArray[offset] = id;
                offset++;
                while (id != last) {    //empty the stack until the last node checked
                    id = stack.pop();
                    onStack[id] = 0;
                    tempArray[offset] = id;
                    offset++;
                }
                Component cmp;         //create the Component
                cmp.included_nodes_count = offset;
                cmp.included_nodes_ids = (uint32_t*) malloc((offset)*sizeof(uint32_t));
                for (uint32_t i = 0; i < offset; i++)
                    cmp.included_nodes_ids[i] = tempArray[i];
                free(tempArray);
                addComponent(&cmp); //add it to the list
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

void SCC::createHyperGraph(){
  list_node* current;
  uint32_t* neighArray;
  uint32_t len;
  uint32_t temp;

  HyperIndex = new NodeIndex();
  HyperBuf = new Buffer();

  uint32_t* edgeExists = (uint32_t*) calloc(components_count, sizeof(uint32_t));
  uint32_t turn = 0;

  //get all the hypergraph nodes indexed
  for(uint32_t i=0; i<components_count; i++){
    temp = HyperBuf->allocNewNode();
    HyperIndex->insertNode(components[i].component_id, temp);
  }


  for(uint32_t i=0; i<components_count; i++){
      turn++;
      for(uint32_t j=0; j<components[i].included_nodes_count; j++){
        if(Out->isIndexed(components[i].included_nodes_ids[j])){

          current = Out_Buf->getListNode(Out->getListHead(components[i].included_nodes_ids[j]));

          while(1) { //loop for all neighbors
              len = current->get_length();
              neighArray = current->get_neighborArray();
              for (uint32_t k = 0; k < len; k++) { //for every node in a list_node
                if(components[i].component_id != id_belongs_to_component[neighArray[k]] && edgeExists[id_belongs_to_component[neighArray[k]]] != turn){
                  edgeExists[id_belongs_to_component[neighArray[k]]] = turn;
                  HyperBuf->addNewEdgeDirectly(id_belongs_to_component[neighArray[k]], components[i].component_id, *HyperIndex);
                }
              }

              if(current->get_hasNext()) { //get the next list_node
                  current = Out_Buf->getListNode(current->get_nextNode());
              }
              else { //break loop if there are no more listnodes
                  break;
              }
          }
        }
      }
  }

  free(edgeExists);
}
