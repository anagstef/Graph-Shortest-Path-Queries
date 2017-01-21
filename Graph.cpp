#include "Graph.h"

using namespace std;

void Graph::clean() {
    ForwardFringe.clear();
    BackwardsFringe.clear();
    ForwardExplored.clear();
    BackwardsExplored.clear();
}

void Graph::createComponents(){
  cc = new CC(In, Out, In_Buf, Out_Buf);
  opAdds = true;
}

void Graph::createSCComponents() {
    scc = new SCC(In, Out, In_Buf, Out_Buf);
}

void Graph::destroyStronglyConnectedComponents() {
    delete(scc);
}

void Graph::rebuildCC(){
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

// int Graph::estimateShortestPathStronglyConnectedComponents(uint32_t from, uint32_t to) {
//     uint32_t temp, popedNode;
//     int cost = 0, len;
//     list_node* current;
//     uint32_t* neighArray;
//
//     //get the neighbors of the two nodes
//     uint32_t forward_neighbors = Out.getNumOfNeighbors(from);
//     uint32_t backwards_neighbors = In.getNumOfNeighbors(to);
//
//     //if one of the nodes does not have any neighbors, then one of them is not indexed
//     if (forward_neighbors == 0 || backwards_neighbors == 0) {
//         return -1;
//     }
//
//     //if it is the same node, then the cost is 0
//     if (from == to){
//         return 0;
//     }
//
//     //search on SCC if nodes are connected
//     if (!scc->nodesBelongToSCC(from, to))
//       return -1;
//     uint32_t ComponentId = scc->findNodeStronglyConnectedComponentID(from);
//     //add the nodes to each Fringe
//     ForwardFringe.push(from);
//     BackwardsFringe.push(to);
//     BackwardsExplored.add(to);
//     ForwardExplored.add(from);
//
//     //loop until solution is found or not found
//     while(1) {
//
//         //If one of the two fringes is empty, then there is no path
//         if (ForwardFringe.isEmpty() || BackwardsFringe.isEmpty())
//              return -1;
//
//         //select to expand the Fringe that has the least next neighbors
//         if ((forward_neighbors <= backwards_neighbors)) {
//             forward_neighbors = ForwardFringe.getSize(); //init the sum
//             temp = ForwardFringe.getSize();
//             cost++;
//
//             //EXPANDING FORWARD BFS
//             for (uint32_t i=0; i<temp; i++) { //for every node in Fringe
//                popedNode = ForwardFringe.pop();
//
//                 //node should be indexed in current Index
//                 if (!Out.isIndexed(popedNode))
//                     continue;
//                 if (!scc->nodeBelongsToSCC(popedNode, ComponentId))
//                     continue;
//                 //get current list node
//                 current = Out_Buf.getListNode(Out.getListHead(popedNode));
//
//                 while (1) { //loop for all neighbors
//                     len = current->get_length();
//                     neighArray = current->get_neighborArray();
//                     for (int j=0; j<len; j++) { //for every node in a list_node
//                       //if node is on the other BFS's explored set then there is path
//                       if (BackwardsExplored.find(neighArray[j])) {
//                           return cost;
//                       }
//                       if (!ForwardExplored.find(neighArray[j])){
//                           ForwardExplored.add(neighArray[j]);
//                           forward_neighbors += Out.getNumOfNeighbors(neighArray[j]);
//                           ForwardFringe.push(neighArray[j]);
//                       }
//                     }
//                     if (current->get_hasNext()) { //get the next list_node
//                         current = Out_Buf.getListNode(current->get_nextNode());
//                     }
//                     else { //break loop if there are no more listnodes
//                         break;
//                     }
//                 }
//             }
//             // cost++; //increment cost
//         } else {
//             backwards_neighbors = BackwardsFringe.getSize();
//             temp = BackwardsFringe.getSize();
//             //temp = BackwardsFringe.size();
//             cost++;
//
//             //EXPANDING BACKWARDS BFS
//             for (uint32_t i=0; i<temp; i++) { //for every node in Fringe
//               // cout << "Size of BackwardsFringe is: " << BackwardsFringe.getSize() << endl;
//                  popedNode = BackwardsFringe.pop();
//                 //popedNode = BackwardsFringe.front();
//                 //BackwardsFringe.pop();
//
//
//
//
//                 // cout << "BACKWARDS: Poped " << popedNode << " from BackwardsFringe" << endl;
//                 // //if goal state return the total cost
//                 // if(Explored.find(popedNode))
//                 //     return cost - 1; //shortest path found
//                 //
//                 // //if this is not a goal, add it to Explored Set
//                 // Explored.add(popedNode);
//
//                 if (!In.isIndexed(popedNode))
//                     continue;
//                 if (!scc->nodeBelongsToSCC(popedNode, ComponentId))
//                     continue;
//                 //get current list node
//                 current = In_Buf.getListNode(In.getListHead(popedNode));
//
//                 while (1) { //loop for all neighbors
//                     len = current->get_length();
//                     neighArray = current->get_neighborArray();
//                     for (int j=0; j<len; j++) { //for every node in a list_node
//                         if (ForwardExplored.find(neighArray[j])) {
//                             //ForwardFringe.clear();
//                             //BackwardsFringe.clear();
//                             return cost;
//                         }
//                         if (!BackwardsExplored.find(neighArray[j])) {
//                             BackwardsExplored.add(neighArray[j]);
//                             backwards_neighbors += In.getNumOfNeighbors(neighArray[j]);
//                             BackwardsFringe.push(neighArray[j]);
//                             // //if the node is not already visited
//                             // if(!Explored.find(neighArray[j])){
//                             //     //add its neighbors to the variable-counter
//                             //     backwards_neighbors += In.getNumOfNeighbors(neighArray[j]);
//                             //     //add it to fringe
//                             //     BackwardsFringe.push(neighArray[j]);
//                             //     cout << "BACKWARDS: Pushed " << neighArray[j] << " to BackwardsFringe" << endl;
//                             // }
//                         }
//                     }
//
//                     if (current->get_hasNext()) { //get the next list_node
//                         current = In_Buf.getListNode(current->get_nextNode());
//                     }
//                     else { //break loop if there are no more listnodes
//                         break;
//                     }
//                 }
//             }
//         }
//     }
// }

int Graph::query(uint32_t from, uint32_t to) {
    int cost = 0;
    BFSnode fringeNode;

    //increase the query counter for the metric
    // cc->increaseQueryNum();

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
    // if(!cc->areNodesConnected(from, to))
    //   return -1;

    int GrailAnswer = scc->querySCC(from, to);
    if(GrailAnswer == -1)
      return -1;


    //BBFS STARTS HERE

    //add the nodes to each Fringe
    if(GrailAnswer == 1)
      fringeNode.sameSCC = true;
    else
      fringeNode.sameSCC = false;
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
