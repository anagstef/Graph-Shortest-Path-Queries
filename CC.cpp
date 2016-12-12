#include "CC.h"

#define DEBUG 0

using namespace std;

CC::CC(NodeIndex& In, NodeIndex& Out, Buffer& In_Buf, Buffer& Out_Buf){
  QueryNum = 0;
  UpdateUsed = 0;
  componentCount = 1;
  offset = 0;
  queue = new Queue<uint32_t>();


  indexsize = In.getSize();
  if (Out.getSize() > indexsize)
    indexsize = Out.getSize();

  ccindex = (uint32_t*) malloc(sizeof(uint32_t) * indexsize);

  for(uint32_t i=0; i<indexsize; i++){
    ccindex[i] = 0;
  }

  while(offset < indexsize){
    if((In.isIndexed(offset) || Out.isIndexed(offset)) && ccindex[offset] == 0){
      CC_BFS(In, Out, In_Buf, Out_Buf);
      componentCount++;
      queue->clear();
    }
    offset++;
  }

  if(DEBUG)
   cout << "Number of CC is " << componentCount - 1 << endl;

  delete queue;
  updateIndex = new UpdateIndex(componentCount);
}

CC::~CC(){
  delete updateIndex;
  free(ccindex);
}

void CC::CC_BFS(NodeIndex& In, NodeIndex& Out, Buffer& In_Buf, Buffer& Out_Buf){
  uint32_t tempQueueSize, tempListNodeLength, popedNode;
  list_node* current;
  uint32_t* neighArray;

  queue->push(offset);
  ccindex[offset] = componentCount;

  while(!queue->isEmpty()){
     tempQueueSize = queue->getSize();

    //EXPANDING FORWARD BFS
    for(uint32_t i=0; i<tempQueueSize; i++){ //for every node in Fringe
        popedNode = queue->pop();

        if(Out.isIndexed(popedNode)){

          //get current list node
          current = Out_Buf.getListNode(Out.getListHead(popedNode));

          while(1){ //loop for all neighbors
              tempListNodeLength = current->get_length();
              neighArray = current->get_neighborArray();
              for(uint32_t j=0; j<tempListNodeLength; j++){ //for every node in a list_node
                  if(ccindex[neighArray[j]] == 0){
                      ccindex[neighArray[j]] = componentCount;
                      queue->push(neighArray[j]);
                  }
              }

              if(current->get_hasNext()){ //get the next list_node
                  current = Out_Buf.getListNode(current->get_nextNode());
              }
              else{ //break loop if there are no more listnodes
                  break;
              }
          }

        }


        if(In.isIndexed(popedNode)){

          //get current list node
          current = In_Buf.getListNode(In.getListHead(popedNode));

          while(1){ //loop for all neighbors
              tempListNodeLength = current->get_length();
              neighArray = current->get_neighborArray();
              for(uint32_t j=0; j<tempListNodeLength; j++){ //for every node in a list_node
                  if(ccindex[neighArray[j]] == 0){
                      ccindex[neighArray[j]] = componentCount;
                      queue->push(neighArray[j]);
                  }
              }

              if(current->get_hasNext()){ //get the next list_node
                  current = In_Buf.getListNode(current->get_nextNode());
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
bool CC::insertNewEdge(uint32_t nodeIdS, uint32_t nodeIdE){
  //if both nodes exist
  if((nodeIdS < indexsize) && (ccindex[nodeIdS] > 0) && (nodeIdE < indexsize) && (ccindex[nodeIdE] > 0)){
    //if they are on the same CC
    if (ccindex[nodeIdS] == ccindex[nodeIdE]) {
      return false;
    }
    else{
      //if it is not already indexed
      if(!updateIndex->isConnected(ccindex[nodeIdS], ccindex[nodeIdE])){
        updateIndex->addEdge(ccindex[nodeIdS], ccindex[nodeIdE]);
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
        new_size = nodeIdS + 5;
        if(new_size <= nodeIdE)
          new_size = nodeIdE + 5;
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
        new_size = nodeIdS + 5;
        if(new_size <= nodeIdE)
          new_size = nodeIdE + 5;
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

bool CC::areNodesConnected(uint32_t nodeIdS, uint32_t nodeIdE){
  if(nodeIdS >= indexsize || nodeIdE >= indexsize)
    return false;

  if (ccindex[nodeIdS] == ccindex[nodeIdE]) {
    return true;
  }
  else{
    UpdateUsed++;
    return updateIndex->isConnected(ccindex[nodeIdS], ccindex[nodeIdE]);
  }
}

bool CC::rebuildIndexes(){
  float value = (float)UpdateUsed / (float)QueryNum;
  cout << "UpdateUsed=" << UpdateUsed << ", QueryNum=" << QueryNum << ". ";
  cout << "Metric value is: " << value;
  if(value >= METRIC){
    cout << "   -Rebuilding..." << endl;
    componentCount = updateIndex->update(ccindex, indexsize, componentCount);
    QueryNum = 0;
    UpdateUsed = 0;
    return true;
  }
  else{
    cout << "   -Will not rebuild..." << endl;
    QueryNum = 0;
    UpdateUsed = 0;
    return false;
  }
}

void CC::increaseQueryNum(){
  QueryNum++;
}
