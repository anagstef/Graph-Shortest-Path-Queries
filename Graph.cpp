#include "Graph.h"

using namespace std;

Graph::Graph(int t){
  threadsNum = t;

  ForwardFringe = (Queue<BFSnode>*) malloc(sizeof(Queue<BFSnode>) * t);
  for (int i = 0; i < t; ++i) {
      new (&ForwardFringe[i]) Queue<BFSnode>(GRAPH_QUEUE_INIT_SIZE);
  }

  BackwardsFringe = (Queue<BFSnode>*) malloc(sizeof(Queue<BFSnode>) * t);
  for (int i = 0; i < t; ++i) {
      new (&BackwardsFringe[i]) Queue<BFSnode>(GRAPH_QUEUE_INIT_SIZE);
  }

  ForwardExplored = (Explored*) malloc(sizeof(Explored) * t);
  for (int i = 0; i < t; ++i) {
      new (&ForwardExplored[i]) Explored(GRAPH_EXPLORED_INIT_SIZE);
  }

  BackwardsExplored = (Explored*) malloc(sizeof(Explored) * t);
  for (int i = 0; i < t; ++i) {
      new (&BackwardsExplored[i]) Explored(GRAPH_EXPLORED_INIT_SIZE);
  }

}

Graph::~Graph(){
  if (isDynamic && cc != NULL)
    delete cc;
  else if (!isDynamic && scc != NULL)
    delete scc;

  for (int i = 0; i < threadsNum; ++i) {
      ForwardFringe[i].~Queue();
      BackwardsFringe[i].~Queue();
      ForwardExplored[i].~Explored();
      BackwardsExplored[i].~Explored();
  }
  free(ForwardFringe);
  free(BackwardsFringe);
  free(ForwardExplored);
  free(BackwardsExplored);
}

void Graph::clear(int i) {
    ForwardFringe[i].clear();
    BackwardsFringe[i].clear();
    ForwardExplored[i].clear();
    BackwardsExplored[i].clear();
}

int Graph::createComponents(){
    if(isDynamic){
        cc = new CC(In, Out, In_Buf, Out_Buf);
        opAdds = true;
        return 1;
    }
    else {
        scc = new SCC(In, Out, In_Buf, Out_Buf);
        return 1;
    }
}

void Graph::rebuildCC(){
  if(isDynamic)
    cc->rebuildIndexes();
}

int Graph::add(uint32_t from, uint32_t to) {
    uint32_t temp;

    InsEdge check;
    check.from = from;
    check.to = to;

    if(duplicates.find(check))
      return -1;
    else
      duplicates.add(check);

    // fprintf(stderr, "%u --> %u : %u\n",from, to, current_version );
    if (Out.isIndexed(from)) { //if the node exists
        Out_Buf.addNewEdgeDirectly(to, from, current_version, Out); //add directly to the end
    } else { //else add the node first to the index and then direct add
        temp = Out_Buf.allocNewNode();
        Out.insertNode(from, temp, current_version);
        Out_Buf.addNewEdgeDirectly(to, from, current_version, Out);
    }


    if (In.isIndexed(to)) {
        In_Buf.addNewEdgeDirectly(from, to, current_version, In);
    } else {
        temp = In_Buf.allocNewNode();
        In.insertNode(to, temp, current_version);
        In_Buf.addNewEdgeDirectly(from, to, current_version, In);
     }

    if(opAdds){
      // cerr << "insert to CC BEGIN" << endl;
      cc->insertNewEdge(from, to, current_version);
      // cerr << "insert to CC done!" << endl;
    }
    return 1;
}

int Graph::query(uint32_t from, uint32_t to, uint32_t version, int threadID) {
    int cost = 0;
    BFSnode fringeNode;

    // increase the query counter for the metric
    if(isDynamic)
      cc->increaseQueryNum();

    //get the neighbors of the two nodes
    uint32_t forward_neighbors = Out.getNumOfNeighbors(from);
    uint32_t ToOutNeighbors = Out.getNumOfNeighbors(to);
    uint32_t backwards_neighbors = In.getNumOfNeighbors(to);
    uint32_t FromInNeighbors = In.getNumOfNeighbors(from);

    //if one of the nodes does not have any neighbors, then one of them is not indexed
    if((forward_neighbors == 0 && FromInNeighbors == 0) || (backwards_neighbors == 0 && ToOutNeighbors == 0)) {
        return -1;
    }

    //if it is the same node, then the cost is 0
    if(from == to){
        return 0;
    }

    //check if there are any edges from these nodes that exist in this version
    // if(isDynamic && (!Out.existsInThisVersion(from, version) || !In.existsInThisVersion(to, version))){
    //   return -1;
    // }

    //search on CC if nodes are connected
    if(isDynamic && !cc->areNodesConnected(from, to, version)){
      return -1;
    }


    if(!isDynamic){
      int GrailAnswer = scc->querySCC(from, to);
      if(GrailAnswer == -1)
        return -1;
      else if(GrailAnswer == 1)
        fringeNode.sameSCC = true;
      else
        fringeNode.sameSCC = false;
    }

    fringeNode.nodeID = from;
    ForwardFringe[threadID].push(fringeNode);
    fringeNode.nodeID = to;
    BackwardsFringe[threadID].push(fringeNode);
    BackwardsExplored[threadID].add(to);
    ForwardExplored[threadID].add(from);

    //loop until solution is found or not found
    while(1){

        //If one of the two fringes is empty, then there is no path
         if(ForwardFringe[threadID].isEmpty() || BackwardsFringe[threadID].isEmpty())
             return -1;

        //select to expand the Fringe that has the least next neighbors
        if((forward_neighbors <= backwards_neighbors)){
          cost++;
          if(SingleLevelBFSExpand(Out, Out_Buf, forward_neighbors, ForwardFringe[threadID], ForwardExplored[threadID], BackwardsExplored[threadID], to, true, version))
            return cost;

        } else{
          cost++;
          if(SingleLevelBFSExpand(In, In_Buf, backwards_neighbors, BackwardsFringe[threadID], BackwardsExplored[threadID], ForwardExplored[threadID], from, false, version))
            return cost;

        }
    }
}

bool Graph::SingleLevelBFSExpand(NodeIndex &Index, Buffer &Buff,
  uint32_t &neighbors, Queue<BFSnode> &Fringe, Explored &explored,
  Explored &Goal, uint32_t &node, bool isForward, uint32_t version){


  BFSnode popedNode, newNode;
  uint32_t temp;
  int len;
  list_node* current;
  uint32_t* neighArray;
  uint32_t* versionArray;
  bool enteredSCC = false;

  neighbors = 0; //init the sum
  temp = Fringe.getSize();

  //EXPAND BFS LEVEL
  for(uint32_t i=0; i<temp; i++){ //for every node in Fringe
     popedNode = Fringe.pop();

      //node should be indexed in current Index
      if(!Index.isIndexed(popedNode.nodeID))
        continue;

      //get current list node
      current = Buff.getListNode(Index.getListHead(popedNode.nodeID));

      while(1){ //loop for all neighbors
          len = current->get_length();
          neighArray = current->get_neighborArray();

          if(isDynamic)
            versionArray = current->get_propertyArray();

          for(int j=0; j<len; j++){ //for every node in a list_node

            if(isDynamic && versionArray[j] > version)
              continue;

            if(!explored.find(neighArray[j])){
                //if node is on the other BFS's explored set then there is path
                if(Goal.find(neighArray[j])) {
                    return true;
                }

                explored.add(neighArray[j]);

                if(!isDynamic){

                  //if node is not in the same SCC and grail returned YES, then ignore the node
                  bool belongsSameSCC = scc->nodesBelongToSameSCC(neighArray[j], node);
                  if(popedNode.sameSCC && !belongsSameSCC)
                    continue;

                  if(!popedNode.sameSCC && isForward && scc->querySCC(neighArray[j], node) == -1)
                    continue;
                  else if(!popedNode.sameSCC && !isForward && scc->querySCC(node, neighArray[j]) == -1)
                    continue;

                  if(belongsSameSCC)
                    enteredSCC = true;
                  else
                    enteredSCC = false;
                }

                if(Index.getNumOfNeighbors(neighArray[j]) > 0){
                  neighbors += Index.getNumOfNeighbors(neighArray[j]);
                  newNode.nodeID = neighArray[j];
                  newNode.sameSCC = enteredSCC;
                  Fringe.push(newNode);
                }

            }
          }

          if(current->get_hasNext()){ //get the next list_node
              current = Buff.getListNode(current->get_nextNode());
          }
          else{ //break loop if there are no more listnodes
              break;
          }
      }
  }

  neighbors += Fringe.getSize();
  return false;
}

//PRINTING GRAPH FOR UNIT TESTING
void Graph::printGraph(){
      uint32_t i,j, indexsize, listHead, len;
      list_node* current;
      uint32_t* neighArray;

      cout << "Outcoming Edges:" << endl;
      indexsize = Out.getSize();

      for(i=0;i<indexsize;i++){
        if(Out.isIndexed(i)){
          listHead = Out.getListHead(i);

          current = Out_Buf.getListNode(listHead);

          while(1){ //loop for all neighbors
              len = current->get_length();
              neighArray = current->get_neighborArray();
              for(j=0; j<len; j++){ //for every node in a list_node
                cout << i << " " << neighArray[j] << endl;
              }

              if(current->get_hasNext()){ //get the next list_node
                  current = Out_Buf.getListNode(current->get_nextNode());
              }
              else{ //break loop if there are no more listnodes
                  break;
              }
          }
        }

      }

      cout << "\n\nIncoming Edges:" << endl;
      indexsize = In.getSize();

      for(i=0;i<indexsize;i++){
        if(In.isIndexed(i)){
          listHead = In.getListHead(i);

          current = In_Buf.getListNode(listHead);

          while(1){ //loop for all neighbors
              len = current->get_length();
              neighArray = current->get_neighborArray();
              for(j=0; j<len; j++){ //for every node in a list_node
                cout << i << " " << neighArray[j] << endl;
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
