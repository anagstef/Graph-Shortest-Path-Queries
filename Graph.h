#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <new>
#include "Buffer.h"
#include "NodeIndex.h"
#include "Queue_.h"
#include "HT_Template.h"
#include "Explored.h"
#include "CC.h"
#include "SCC.h"

#define HT_GRAPH_HASH_SIZE 113063
#define HT_GRAPH_BUCKET_SIZE 20
#define GRAPH_QUEUE_INIT_SIZE 1000
#define GRAPH_EXPLORED_INIT_SIZE 1000

class CC;
class SCC;

struct InsEdge{
  uint32_t from;
  uint32_t to;
  int operator%(const int& a) const{
    return (from + to)%a;
  }
  bool operator==(const InsEdge& a) const{
    if (a.from == from && a.to == to)
      return true;
    else
      return false;
  }
};


class Graph {
private:
    NodeIndex In; //index for incoming edges
    NodeIndex Out;//index for outcoming edges
    Buffer In_Buf;//buffer for incoming edges
    Buffer Out_Buf;//buffer for outcoming edges
    Queue<uint32_t> ForwardFringe{GRAPH_QUEUE_INIT_SIZE};
    Queue<uint32_t> BackwardsFringe{GRAPH_QUEUE_INIT_SIZE};
    Explored ForwardExplored{GRAPH_EXPLORED_INIT_SIZE};
    Explored BackwardsExplored{GRAPH_EXPLORED_INIT_SIZE};
    HashTable<InsEdge> duplicates{HT_GRAPH_HASH_SIZE, HT_GRAPH_BUCKET_SIZE};
    CC* cc;
    SCC* scc;
    bool opAdds = false;
    bool isDynamic;
public:

    void createComponents();
    void createSCComponents();
    void rebuildCC();
    void destroyStronglyConnectedComponents();
    // int estimateShortestPathStronglyConnectedComponents(uint32_t source_node, uint32_t target_node);
    void add(uint32_t from, uint32_t to); //add a new edge
    int query(uint32_t from, uint32_t to); //search for the shortest path and return it
    bool SingleLevelBFSExpand(NodeIndex &Index, Buffer &Buff, uint32_t &neighbors, Queue<uint32_t> &Fringe, Explored &explored, Explored &Goal, int &GrailAnswer, uint32_t &SCCnum);
    void printGraph(); //unit testing
    void clean();
    NodeIndex getIn()  { return In; }
    NodeIndex getOut() { return Out;}
    Buffer getBIn()    { return In_Buf; }
    Buffer getBOut()   { return Out_Buf;}
};

#endif
