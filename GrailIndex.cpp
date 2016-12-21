#include "GrailIndex.h"

using namespace std;

GrailIndex::GrailIndex(NodeIndex& HyperIndex, Buffer& HyperBuf){
  this->HyperIndex = &HyperIndex;
  this->HyperBuf = &HyperBuf;

  grail_size = HyperIndex->getSize();
  rank = 1;

  grail = (grailNode*) malloc(sizeof(grailNode) * grail_size);

  for(uint32_t i = 0; i < grail_size; i++){
    if(HyperIndex->isIndexed(i)){
      grail[i].rank = 0;
      grail[i].minrank = 0;
      grail[i].iterator = 0;
      grail[i].numOfNeighbors = HyperIndex->getNumOfNeighbors(i);

      if(grail[i].numOfNeighbors > 0)
        grail[i].neighbors = createHyperNeighborsArray(i);
    }
  }

}

GrailIndex::~GrailIndex(){
  for(uint32_t i = 0; i < grail_size; i++){
    if(grail[i].numOfNeighbors > 0)
      free(grail[i].neighbors);
  }
  free(grail);
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
          else { //break loop if there are no more listnodes
              return retValue;
          }
    }
}
