#include "GrailIndex.h"

using namespace std;

GrailIndex::GrailIndex(NodeIndex& HyperIndex, Buffer& HyperBuf){
  this->HyperIndex = &HyperIndex;
  this->HyperBuf = &HyperBuf;
  uint32_t last_indexed;

  grail_size = HyperIndex.getSize();

  grail[0] = (grailNode*) malloc(sizeof(grailNode) * grail_size);

  srand(time(NULL));

  //creating the Grail Index nodes
  for(uint32_t i = 0; i < grail_size; i++){
    if(HyperIndex.isIndexed(i)){
      last_indexed = i;
      grail[0][i].nodeID = i;
      grail[0][i].rank = 0;
      grail[0][i].minrank = 0;
      grail[0][i].iterator = 0;
      grail[0][i].numOfNeighbors = HyperIndex.getNumOfNeighbors(i);

      if(grail[0][i].numOfNeighbors > 0)
        grail[0][i].neighbors = createHyperNeighborsArray(i);
    }
  }

  grail_size = last_indexed + 1;

  for(int k=1; k<GRAIL_INDEXES; k++)
    grail[k] = (grailNode*) malloc(sizeof(grailNode) * grail_size);

  for(int k=1; k<GRAIL_INDEXES; k++){
      for(uint32_t i = 0; i < grail_size; i++){
        grail[k][i].nodeID = grail[0][i].nodeID;
        grail[k][i].rank = 0;
        grail[k][i].minrank = 0;
        grail[k][i].iterator = 0;
        grail[k][i].numOfNeighbors = grail[0][i].numOfNeighbors;
        grail[k][i].neighbors = grail[0][i].neighbors;
      }
  }

  //Shuffling nodes
  if (grail_size >= 2){
    for(int k=0; k<GRAIL_INDEXES; k++){
      for (uint32_t i = grail_size - 1; i > 0; i--) {
        uint32_t j = rand() % (i+1);
        grailNode swap = grail[k][i];
        grail[k][i] = grail[k][j];
        grail[k][j] = swap;
      }
    }
  }

  for(int k=0; k<GRAIL_INDEXES; k++)
    invertedIndex[k] = (uint32_t*) malloc(sizeof(uint32_t) * grail_size);

  //Creating an Inverted Index for the Grail nodes
  for(int k=0; k<GRAIL_INDEXES; k++){
    for(uint32_t i = 0; i < grail_size; i++){
      invertedIndex[k][grail[k][i].nodeID] = i;
    }
  }

  stack = new Stack<uint32_t>(GRAIL_STACK_INIT_SIZE);

  //create grails
  for(int k=0; k<GRAIL_INDEXES; k++){
    rank = 1;

    for(uint32_t n=0; n<grail_size; n++){
      if (grail[k][n].numOfNeighbors >= 2){
        for (uint32_t i = grail[k][n].numOfNeighbors - 1; i > 0; i--) {
          uint32_t j = rand() % (i+1);
          uint32_t swap = grail[k][n].neighbors[i];
          grail[k][n].neighbors[i] = grail[k][n].neighbors[j];
          grail[k][n].neighbors[j] = swap;
        }
      }
    }

    for (uint32_t i = 0; i < grail_size; i++) {
        if (grail[k][i].rank == 0) {
            GrailDFS(grail[k][i].nodeID, grail[k], invertedIndex[k]);
        }
    }
  }

  delete stack;
  for(uint32_t i = 0; i < grail_size; i++){
    if(grail[0][i].numOfNeighbors > 0)
      free(grail[0][i].neighbors);
  }

}

void GrailIndex::GrailDFS(uint32_t current, grailNode* grail, uint32_t* invertedIndex){
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
  // for(uint32_t i = 0; i < grail_size; i++){
  //   if(grail[i].numOfNeighbors > 0)
  //     free(grail[i].neighbors);
  // }
  for(int k=0;k<GRAIL_INDEXES; k++){
    free(grail[k]);
    free(invertedIndex[k]);
  }
}

//Return True for "Maybe", False for "No"
bool GrailIndex::askGrail(uint32_t X, uint32_t Y){
  for(int k=0;k<GRAIL_INDEXES; k++){
    if(!(grail[k][invertedIndex[k][X]].minrank <= grail[k][invertedIndex[k][Y]].minrank
            && grail[k][invertedIndex[k][Y]].minrank <= grail[k][invertedIndex[k][X]].rank
            && grail[k][invertedIndex[k][X]].minrank <= grail[k][invertedIndex[k][Y]].rank
            && grail[k][invertedIndex[k][Y]].rank <= grail[k][invertedIndex[k][X]].rank))
    return false;
  }
  return true;
  // return (grail[invertedIndex[X]].minrank <= grail[invertedIndex[Y]].minrank
  //         && grail[invertedIndex[Y]].minrank <= grail[invertedIndex[X]].rank
  //         && grail[invertedIndex[X]].minrank <= grail[invertedIndex[Y]].rank
  //         && grail[invertedIndex[Y]].rank <= grail[invertedIndex[X]].rank);
}

//create an array of neighbors of each CC in HyperGraph
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
          // if (iterator >= 2){
          //   for (uint32_t i = iterator - 1; i > 0; i--) {
          //     uint32_t j = rand() % (i+1);
          //     uint32_t swap = retValue[i];
          //     retValue[i] = retValue[j];
          //     retValue[j] = swap;
          //   }
          // }
          return retValue;
        }
    }
}
