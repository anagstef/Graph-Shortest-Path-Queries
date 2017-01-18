#include "GrailIndex.h"

using namespace std;

GrailIndex::GrailIndex(NodeIndex& HyperIndex, Buffer& HyperBuf){
  this->HyperIndex = &HyperIndex;
  this->HyperBuf = &HyperBuf;
  uint32_t last_indexed;

  grail_size = HyperIndex.getSize();
  rank = 1;

  grail = (grailNode*) malloc(sizeof(grailNode) * grail_size);

  srand(time(NULL));

  //creating the Grail Index nodes
  for(uint32_t i = 0; i < grail_size; i++){
    if(HyperIndex.isIndexed(i)){
      last_indexed = i;
      grail[i].nodeID = i;
      grail[i].rank = 0;
      grail[i].minrank = 0;
      grail[i].iterator = 0;
      grail[i].numOfNeighbors = HyperIndex.getNumOfNeighbors(i);

      if(grail[i].numOfNeighbors > 0)
        grail[i].neighbors = createHyperNeighborsArray(i);
    }
  }

  grail_size = last_indexed + 1;

  //Shuffling nodes
  if (grail_size >= 2){
    for (uint32_t i = grail_size - 1; i > 0; i--) {
      uint32_t j = rand() % (i+1);
      grailNode swap = grail[i];
      grail[i] = grail[j];
      grail[j] = swap;
    }
  }

  invertedIndex = (uint32_t*) malloc(sizeof(uint32_t) * grail_size);

  //Creating an Inverted Index for the Grail nodes
  for(uint32_t i = 0; i < grail_size; i++){
    invertedIndex[grail[i].nodeID] = i;
  }

  stack = new Stack<uint32_t>(GRAIL_STACK_INIT_SIZE);

  for (uint32_t i = 0; i < grail_size; i++) {
      if (grail[i].rank == 0) {
          GrailDFS(grail[i].nodeID);
      }
  }

  delete stack;

}

void GrailIndex::GrailDFS(uint32_t current){
  uint32_t tempMinRank;
  while (1) {
    //if there are more neighbors on this node to explore
    if (grail[invertedIndex[current]].iterator < grail[invertedIndex[current]].numOfNeighbors) {
        grail[invertedIndex[current]].iterator++;
        stack->push(current);
        current = grail[invertedIndex[current]].neighbors[grail[invertedIndex[current]].iterator - 1];
        //if neighbor already explored by other DFS call, just update its rank
        if (grail[invertedIndex[current]].rank != 0) {
          tempMinRank = grail[invertedIndex[current]].minrank;
          current = stack->pop();
          if(grail[invertedIndex[current]].minrank == 0 || tempMinRank < grail[invertedIndex[current]].minrank)
            grail[invertedIndex[current]].minrank = tempMinRank;
        }
    }
    else { //if no more neighbors, or no neighbors at all
      //set current rank
      grail[invertedIndex[current]].rank = rank;
      //set minrank = rank if the node has no neighbors
      if(grail[invertedIndex[current]].minrank == 0){
        grail[invertedIndex[current]].minrank = rank;
      }

      rank++;

      if(stack->isEmpty()) //DFS reached root
        return;

      tempMinRank = grail[invertedIndex[current]].minrank;
      current = stack->pop();
      if(grail[invertedIndex[current]].minrank == 0 || tempMinRank < grail[invertedIndex[current]].minrank)
        grail[invertedIndex[current]].minrank = tempMinRank;

    }
  }

}

GrailIndex::~GrailIndex(){
  for(uint32_t i = 0; i < grail_size; i++){
    if(grail[i].numOfNeighbors > 0)
      free(grail[i].neighbors);
  }
  free(grail);
  free(invertedIndex);
}

//Return True for "Maybe", False for "No"
bool GrailIndex::askGrail(uint32_t X, uint32_t Y){
  return (grail[invertedIndex[X]].minrank <= grail[invertedIndex[Y]].minrank
          && grail[invertedIndex[Y]].minrank <= grail[invertedIndex[X]].rank
          && grail[invertedIndex[X]].minrank <= grail[invertedIndex[Y]].rank
          && grail[invertedIndex[Y]].rank <= grail[invertedIndex[X]].rank);
}


uint32_t* GrailIndex::createHyperNeighborsArray(uint32_t nodeId) {
    list_node* current;
    uint32_t* neighArray;
    uint32_t len;
    uint32_t* retValue;
    uint32_t iterator = 0;

    retValue = (uint32_t*) malloc(sizeof(uint32_t) * HyperIndex->getNumOfNeighbors(nodeId));
    //get current list node
    current = HyperBuf->getListNode(HyperIndex->getListHead(nodeId));

    while(1) { //loop for all neighbors
        len = current->get_length();
        neighArray = current->get_neighborArray();
        for (uint32_t j = 0; j < len; j++) { //for every node in a list_node
          retValue[iterator] = neighArray[j];
          iterator++;
        }

        if(current->get_hasNext()) { //get the next list_node
            current = HyperBuf->getListNode(current->get_nextNode());
        }
        else { //if there are no more neighbors to add, then shuffle them
          if (iterator >= 2){
            for (uint32_t i = iterator - 1; i > 0; i--) {
              uint32_t j = rand() % (i+1);
              uint32_t swap = retValue[i];
              retValue[i] = retValue[j];
              retValue[j] = swap;
            }
          }
          return retValue;
        }
    }
}
