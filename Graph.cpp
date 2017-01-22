#include "Graph.h"

using namespace std;

Graph::~Graph(){
  if(isDynamic)
    delete cc;
  else
    delete scc;
}

void Graph::clean() {
    ForwardFringe.clear();
    BackwardsFringe.clear();
    ForwardExplored.clear();
    BackwardsExplored.clear();
}

void Graph::createComponents(){
  if(isDynamic){
    cc = new CC(In, Out, In_Buf, Out_Buf);
    opAdds = true;
  }
  else
    scc = new SCC(In, Out, In_Buf, Out_Buf);
}

void Graph::rebuildCC(){
  if(isDynamic)
    cc->rebuildIndexes();
}

void Graph::add(uint32_t from, uint32_t to) {
    uint32_t temp;
    //bool NewEdgeAdded;

    InsEdge check;
    check.from = from;
    check.to = to;

    if(duplicates.find(check))
      return;
    else
      duplicates.add(check);


    if (Out.isIndexed(from)) { //if the node exists
        Out_Buf.addNewEdgeDirectly(to, from, Out); //add directly to the end
    } else { //else add the node first to the index and then direct add
        temp = Out_Buf.allocNewNode();
        Out.insertNode(from, temp);
        Out_Buf.addNewEdgeDirectly(to, from, Out);
    }


    if (In.isIndexed(to)) {
        In_Buf.addNewEdgeDirectly(from, to, In);
    } else {
        temp = In_Buf.allocNewNode();
        In.insertNode(to, temp);
        In_Buf.addNewEdgeDirectly(from, to, In);
     }

    if(opAdds)
      cc->insertNewEdge(from, to);
    return;
}

int Graph::query(uint32_t from, uint32_t to) {
    int cost = 0;
    BFSnode fringeNode;

    // increase the query counter for the metric
    if(isDynamic)
      cc->increaseQueryNum();

    //get the neighbors of the two nodes
    uint32_t forward_neighbors = Out.getNumOfNeighbors(from);
    uint32_t backwards_neighbors = In.getNumOfNeighbors(to);

    //if one of the nodes does not have any neighbors, then one of them is not indexed
    if((forward_neighbors == 0 && In.getNumOfNeighbors(from) == 0) || (backwards_neighbors == 0 && Out.getNumOfNeighbors(to) == 0)) {
        return -1;
    }

    //if it is the same node, then the cost is 0
    if(from == to){
        return 0;
    }

    //search on CC if nodes are connected
    if(isDynamic && !cc->areNodesConnected(from, to)){
      // std::cerr << "KLSPR22222" << std::endl;
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
    ForwardFringe.push(fringeNode);
    fringeNode.nodeID = to;
    BackwardsFringe.push(fringeNode);
    BackwardsExplored.add(to);
    ForwardExplored.add(from);

    //loop until solution is found or not found
    while(1){

        //If one of the two fringes is empty, then there is no path
         if(ForwardFringe.isEmpty() || BackwardsFringe.isEmpty())
             return -1;

        //select to expand the Fringe that has the least next neighbors
        if((forward_neighbors <= backwards_neighbors)){
          cost++;
          if(SingleLevelBFSExpand(Out, Out_Buf, forward_neighbors, ForwardFringe, ForwardExplored, BackwardsExplored, to, true))
            return cost;

        } else{
          cost++;
          if(SingleLevelBFSExpand(In, In_Buf, backwards_neighbors, BackwardsFringe, BackwardsExplored, ForwardExplored, from, false))
            return cost;

        }
    }
}

bool Graph::SingleLevelBFSExpand(NodeIndex &Index, Buffer &Buff, uint32_t &neighbors, Queue<BFSnode> &Fringe, Explored &explored, Explored &Goal, uint32_t &node, bool isForward){
  BFSnode popedNode, newNode;
  uint32_t temp;
  int len;
  list_node* current;
  uint32_t* neighArray;
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
          for(int j=0; j<len; j++){ //for every node in a list_node

            // if(popedNode.sameSCC == true && !belongsSameSCC == false)
            //   continue;

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
