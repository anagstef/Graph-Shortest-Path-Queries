#include "Graph.h"

using namespace std;

void Graph::add(uint32_t from, uint32_t to) {
    uint32_t temp;
    bool NewEdgeAdded;

    //get the number of neighbors for each node
    uint32_t from_neighbors = Out.getNumOfNeighbors(from);
    uint32_t to_neighbors = In.getNumOfNeighbors(to);

    //if one of these has zero neighbors, then the edge does not exist
    if(from_neighbors == 0 || to_neighbors == 0) {

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
        return;
    }

    //if the number of neighbors is less for on of the nodes
    if(from_neighbors <= to_neighbors){

        if (Out.isIndexed(from)) { //add the node while checking for duplicates
            NewEdgeAdded = Out_Buf.addNewEdge(to, from, Out);
        } else {
            temp = Out_Buf.allocNewNode();
            Out.insertNode(from, temp);
            NewEdgeAdded = Out_Buf.addNewEdge(to, from, Out);
        }

        if (NewEdgeAdded) { //add the node directly, if it wasnt found as duplicate
            if (In.isIndexed(to)) {
                In_Buf.addNewEdgeDirectly(from, to, In);
            } else {
                temp = In_Buf.allocNewNode();
                In.insertNode(to, temp);
                In_Buf.addNewEdgeDirectly(from, to, In);
            }
        }
        return;

    }

    //the other way around
    if(from_neighbors > to_neighbors){

        if (In.isIndexed(to)) {
            NewEdgeAdded = In_Buf.addNewEdge(from, to, In);
        } else {
            temp = In_Buf.allocNewNode();
            In.insertNode(to, temp);
            NewEdgeAdded = In_Buf.addNewEdge(from, to, In);
        }

        if (NewEdgeAdded) {
            if (Out.isIndexed(from)) {
                Out_Buf.addNewEdgeDirectly(to, from, Out);
            } else {
                temp = Out_Buf.allocNewNode();
                Out.insertNode(from, temp);
                Out_Buf.addNewEdgeDirectly(to, from, Out);
            }
        }
        return;

    }
}


int Graph::query(uint32_t from, uint32_t to) {
    Queue ForwardFringe, BackwardsFringe;
    uint32_t temp, popedNode;
    HashTable Explored;
    int cost = 0, len;
    list_node* current;
    uint32_t* neighArray;

    // //////////////////////////////////////////////
    // ///////////// SIMPLE BFS /////////////////////
    // //////////////////////////////////////////////
    //
    // //get the neighbors of the two nodes
    // uint32_t forward_neighbors = Out.getNumOfNeighbors(from);
    // uint32_t backwards_neighbors = In.getNumOfNeighbors(to);
    //
    // //if one of the nodes dows not have any neighbors, then one of them is not indexed
    // if(forward_neighbors == 0 || backwards_neighbors == 0) {
    //     return -1;
    // }
    //
    // //if it is the same node, then the cost is 0
    // if(from == to){
    //     return 0;
    // }
    //
    // ForwardFringe.push(from);
    //
    // while(1){
    //
    //     //If one of the two fringes is empty, then there is no path
    //     if(ForwardFringe.isEmpty())
    //         return -1;
    //
    //       // if(ForwardFringe.empty())//////////////////////////
    //       //   return -1;
    //
    //       temp = ForwardFringe.getSize();
    //       // temp = ForwardFringe.size();//////////////////
    //
    //       //EXPANDING FORWARD BFS
    //       for(uint32_t i=0; i<temp; i++){ //for every node in Fringe
    //           popedNode = ForwardFringe.pop();
    //           // popedNode = ForwardFringe.front();///////////
    //           // ForwardFringe.pop();//////////////////////
    //           //if goal state return the total cost
    //           if(Explored.find(popedNode))
    //           // if(Explored.find(popedNode) != Explored.end())///////////////////////////
    //               return cost; //shortest path found
    //
    //           //if this is not a goal, add it to Explored Set
    //           Explored.add(popedNode);
    //           // Explored.insert(popedNode);//////////////////////////////////////
    //
    //           //get current list node
    //           current = Out_Buf.getListNode(Out.getListHead(popedNode));
    //
    //           while(1){ //loop for all neighbors
    //               len = current->get_length();
    //               neighArray = current->get_neighborArray();
    //               for(int j=0; j<len; j++){ //for every node in a list_node
    //                   //if the node is not already visited
    //                   if(!Explored.find(neighArray[j]))
    //                   // if(Explored.find(neighArray[j]) == Explored.end()){////////////////////////////////
    //                       //add it to fringe
    //                       ForwardFringe.push(neighArray[j]);
    //                   // }
    //               }
    //
    //               if(current->get_hasNext()){ //get the next list_node
    //                   current = Out_Buf.getListNode(current->get_nextNode());
    //               }
    //               else{ //break loop if there are no more listnodes
    //                   break;
    //               }
    //           }
    //
    //       }
    //       cost++; //increment cost
    // } //while(1)
    //
    //
    // //////////////////////////////////////////////
    // /////////////////// END //////////////////////
    // //////////////////////////////////////////////

    //get the neighbors of the two nodes
    uint32_t forward_neighbors = Out.getNumOfNeighbors(from);
    uint32_t backwards_neighbors = In.getNumOfNeighbors(to);

    //if one of the nodes dows not have any neighbors, then one of them is not indexed
    if(forward_neighbors == 0 || backwards_neighbors == 0) {
        return -1;
    }

    //if it is the same node, then the cost is 0
    if(from == to){
        return 0;
    }

    //add the nodes to each Fringe
    ForwardFringe.push(from);
    BackwardsFringe.push(to);

    //loop until solution is found or not found
    while(1){

        //If one of the two fringes is empty, then there is no path
        if(ForwardFringe.isEmpty() || BackwardsFringe.isEmpty())
            return -1;


        //select to expand the Fringe that has the least next neighbors
        if(forward_neighbors <= backwards_neighbors){
            forward_neighbors = 0; //init the sum
            temp = ForwardFringe.getSize();

            //EXPANDING FORWARD BFS
            for(uint32_t i=0; i<temp; i++){ //for every node in Fringe
                popedNode = ForwardFringe.pop();
                //if goal state return the total cost
                if(Explored.find(popedNode))
                    return cost; //shortest path found

                //if this is not a goal, add it to Explored Set
                Explored.add(popedNode);

                //get current list node
                current = Out_Buf.getListNode(Out.getListHead(popedNode));

                while(1){ //loop for all neighbors
                    len = current->get_length();
                    neighArray = current->get_neighborArray();
                    for(int j=0; j<len; j++){ //for every node in a list_node
                        //if the node is not already visited
                        if(!Explored.find(neighArray[j])){
                            //add its neighbors to the variable-counter
                            forward_neighbors += Out.getNumOfNeighbors(neighArray[j]);
                            //add it to fringe
                            ForwardFringe.push(neighArray[j]);
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
            cost++; //increment cost
        } else{
            backwards_neighbors = 0;
            temp = BackwardsFringe.getSize();

            //EXPANDING BACKWARDS BFS
            for(uint32_t i=0; i<temp; i++){ //for every node in Fringe
                popedNode = BackwardsFringe.pop();
                //if goal state return the total cost
                if(Explored.find(popedNode))
                    return cost; //shortest path found

                //if this is not a goal, add it to Explored Set
                Explored.add(popedNode);

                //get current list node
                current = In_Buf.getListNode(In.getListHead(popedNode));

                while(1){ //loop for all neighbors
                    len = current->get_length();
                    neighArray = current->get_neighborArray();
                    for(int j=0; j<len; j++){ //for every node in a list_node
                        //if the node is not already visited
                        if(!Explored.find(neighArray[j])){
                            //add its neighbors to the variable-counter
                            backwards_neighbors += In.getNumOfNeighbors(neighArray[j]);
                            //add it to fringe
                            BackwardsFringe.push(neighArray[j]);
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
            cost++; //increment cost
        }

    } //while(1)
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
