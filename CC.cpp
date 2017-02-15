#include "CC.h"

#define DEBUG 0

using namespace std;

CC::CC(NodeIndex& In, NodeIndex& Out, Buffer& In_Buf, Buffer& Out_Buf){
  QueryNum = 0;
  UpdateUsed = 0;
  this->In = &In;
  this->Out = &Out;
  this->In_Buf = &In_Buf;
  this->Out_Buf = &Out_Buf;
  pthread_mutex_init(&UpdateUsed_mtx, NULL);
  pthread_mutex_init(&QueryNum_mtx, NULL);

  indexsize = In.getSize();
  if (Out.getSize() > indexsize)
    indexsize = Out.getSize();

  ccindex = (uint32_t*) malloc(sizeof(uint32_t) * indexsize);

  estimateConnectedComponents();

  updateIndex = new UpdateIndex(componentCount);
}


void CC::estimateConnectedComponents(){
  componentCount = 1;
  offset = 0;

  uint32_t maxsize = In->getSize();
  if (Out->getSize() > maxsize)
    maxsize = Out->getSize();


  if(maxsize > indexsize)
    maxsize = indexsize;

  for(uint32_t i=0; i<maxsize; i++){
    ccindex[i] = 0;
  }

  while(offset < maxsize){
    if((In->isIndexed(offset) || Out->isIndexed(offset)) && ccindex[offset] == 0){
      CC_BFS();
      componentCount++;
      queue.clear();
    }
    offset++;
  }

  if(DEBUG)
   cerr << "Number of CC is " << componentCount - 1 << endl;

}

CC::~CC(){
  pthread_mutex_destroy(&UpdateUsed_mtx);
  pthread_mutex_destroy(&QueryNum_mtx);
  delete updateIndex;
  free(ccindex);
}

//use bfs to create CC
void CC::CC_BFS(){
  uint32_t tempQueueSize, tempListNodeLength, popedNode;
  list_node* current;
  uint32_t* neighArray;

  queue.push(offset);
  ccindex[offset] = componentCount;

  while(!queue.isEmpty()){
     tempQueueSize = queue.getSize();

    //EXPANDING FORWARD BFS
    for(uint32_t i=0; i<tempQueueSize; i++){ //for every node in Fringe
        popedNode = queue.pop();

        if(Out->isIndexed(popedNode)){

          //get current list node
          current = Out_Buf->getListNode(Out->getListHead(popedNode));

          while(1){ //loop for all neighbors
              tempListNodeLength = current->get_length();
              neighArray = current->get_neighborArray();
              for(uint32_t j=0; j<tempListNodeLength; j++){ //for every node in a list_node
                  if(ccindex[neighArray[j]] == 0){
                      ccindex[neighArray[j]] = componentCount;
                      queue.push(neighArray[j]);
                  }
              }

              if(current->get_hasNext()){ //get the next list_node
                  current = Out_Buf->getListNode(current->get_nextNode());
              }
              else{ //break loop if there are no more listnodes
                  break;
              }
          }

        }


        if(In->isIndexed(popedNode)){

          //get current list node
          current = In_Buf->getListNode(In->getListHead(popedNode));

          while(1){ //loop for all neighbors
              tempListNodeLength = current->get_length();
              neighArray = current->get_neighborArray();
              for(uint32_t j=0; j<tempListNodeLength; j++){ //for every node in a list_node
                  if(ccindex[neighArray[j]] == 0){
                      ccindex[neighArray[j]] = componentCount;
                      queue.push(neighArray[j]);
                  }
              }

              if(current->get_hasNext()){ //get the next list_node
                  current = In_Buf->getListNode(current->get_nextNode());
              }
              else{ //break loop if there are no more listnodes
                  break;
              }
          }

        }

    }

  }

}

//returns true if something cahnged, else false
bool CC::insertNewEdge(uint32_t nodeIdS, uint32_t nodeIdE, uint32_t version){
  //if both nodes exist
  if((nodeIdS < indexsize) && (ccindex[nodeIdS] > 0) && (nodeIdE < indexsize) && (ccindex[nodeIdE] > 0)){
    //if they are on the same CC, do nothing
    if (ccindex[nodeIdS] == ccindex[nodeIdE]) {
      return false;
    }
    else{
      //if it is not already indexed
      // cerr << "asking isConnected" << endl;
      if(!updateIndex->isConnected(ccindex[nodeIdS], ccindex[nodeIdE], version)){
        // cerr << "it is not" << endl;
        updateIndex->addEdge(ccindex[nodeIdS], ccindex[nodeIdE], version);
        // cerr << "edge added" << endl;
        return true;
      }
      return false;
    }
  }

  //if both nodes do not exist
  if(((nodeIdS >= indexsize) || (ccindex[nodeIdS] == 0)) && ((nodeIdE >= indexsize) || (ccindex[nodeIdE] == 0))){
    //if one or both of the nodes exceeds the index
    if((nodeIdS >= indexsize) || (nodeIdE >= indexsize)){
      //get the new size
      uint32_t new_size = indexsize * 2;
      if ((nodeIdS >= new_size) || (nodeIdE >= new_size)) {
        new_size = nodeIdS * 2;
        if(new_size <= nodeIdE)
          new_size = nodeIdE * 2;
      }

      ccindex = (uint32_t*) realloc(ccindex, sizeof(uint32_t) * new_size);
      for(uint32_t i=indexsize; i<new_size; i++){
        ccindex[i] = 0;
      }
      indexsize = new_size;
    }

    ccindex[nodeIdS] = componentCount;
    ccindex[nodeIdE] = componentCount;
    componentCount++;
    return true;
  }
  else{//if one of the nodes exists
    //if one of the nodes exceeds the index
    if((nodeIdS >= indexsize) || (nodeIdE >= indexsize)){
      //get the new size
      uint32_t new_size = indexsize * 2;
      if ((nodeIdS >= new_size) || (nodeIdE >= new_size)) {
        new_size = nodeIdS * 2;
        if(new_size <= nodeIdE)
          new_size = nodeIdE * 2;
      }

      ccindex = (uint32_t*) realloc(ccindex, sizeof(uint32_t) * new_size);
      for(uint32_t i=indexsize; i<new_size; i++){
        ccindex[i] = 0;
      }
      indexsize = new_size;
    }

    if(ccindex[nodeIdS] > 0)
      ccindex[nodeIdE] = ccindex[nodeIdS];
    else
      ccindex[nodeIdS] = ccindex[nodeIdE];

    return true;
  }
}

//ask CC index if two nodes are connected
bool CC::areNodesConnected(uint32_t nodeIdS, uint32_t nodeIdE, uint32_t version){
  if(nodeIdS >= indexsize || nodeIdE >= indexsize)
    return false;

  if (ccindex[nodeIdS] == ccindex[nodeIdE]) {
    return true;
  }
  else{
    pthread_mutex_lock(&UpdateUsed_mtx);
    UpdateUsed++;
    pthread_mutex_unlock(&UpdateUsed_mtx);
    if(updateIndex->isConnected(ccindex[nodeIdS], ccindex[nodeIdE], version)){
      return true;
    }
    else
      return false;
  }
}

//rebuild CC
bool CC::rebuildIndexes(){
  float value = (float)UpdateUsed / (float)QueryNum;
  if(DEBUG){
    // updateIndex->printHTsize();
    cerr << "UpdateUsed=" << UpdateUsed << ", QueryNum=" << QueryNum << ". ";
    cerr << "Metric value is: " << value;
  }
  if(value >= METRIC){ //if greater than metric then rebuild
    if(DEBUG)
      cerr << "   -Rebuilding..." << endl;
    // componentCount = updateIndex->update(ccindex, indexsize, componentCount);
    estimateConnectedComponents();
    updateIndex->clear();
    QueryNum = 0;
    UpdateUsed = 0;
    return true;
  }
  else{ //do nothing, just initialize vars
    if(DEBUG)
      cerr << "   -Will not rebuild..." << endl;
    QueryNum = 0;
    UpdateUsed = 0;
    return false;
  }
}

void CC::increaseQueryNum(){
  pthread_mutex_lock(&QueryNum_mtx);
  QueryNum++;
  pthread_mutex_unlock(&QueryNum_mtx);
}
