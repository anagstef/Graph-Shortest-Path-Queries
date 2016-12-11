#include "CC.h"

#define DEBUG 0

using namespace std;

CC::CC(Graph& g){
  graph = g;
  componentCount = 1;
  offset = 0;

  indexsize = graph->In.getSize();
  if (graph->Out.getSize() > indexsize)
    indexsize = graph->Out.getSize();

  ccindex = (uint32_t*) malloc(sizeof(uint32_t) * indexsize);

  for(uint32_t i=0; i<indexsize; i++){
    ccindex[i] = 0;
  }

  while(offset < indexsize){
    if((graph->In.isIndexed(offset) || graph->Out.isIndexed(offset)) && ccindex[offset] == 0){
      CC_BFS();
      componentCount++;
      queue.clear();
    }
    offset++;
  }

  if(DEBUG)
   cout << "Number of CC is " << componentCount - 1 << endl;

  UpdateIndex = new UpdateIndex(componentCount);
}

CC::~CC(){
  free(ccindex);
}

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

        if(graph->Out.isIndexed(popedNode)){

          //get current list node
          current = graph->Out_Buf.getListNode(graph->Out.getListHead(popedNode));

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
                  current = graph->Out_Buf.getListNode(current->get_nextNode());
              }
              else{ //break loop if there are no more listnodes
                  break;
              }
          }

        }


        if(graph->In.isIndexed(popedNode)){

          //get current list node
          current = graph->In_Buf.getListNode(graph->In.getListHead(popedNode));

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
                  current = graph->In_Buf.getListNode(current->get_nextNode());
              }
              else{ //break loop if there are no more listnodes
                  break;
              }
          }

        }

    }

  }

}
