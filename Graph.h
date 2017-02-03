#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <new>
#include "Buffer.h"
#include "NodeIndex.h"
#include "Explored.h"
#include "CC.h"
#include "SCC.h"
#include "Templates.h"

// #define HT_GRAPH_HASH_SIZE 10007
#define HT_GRAPH_HASH_SIZE 1000003
#define HT_GRAPH_BUCKET_SIZE 30
#define GRAPH_QUEUE_INIT_SIZE 10000
#define GRAPH_EXPLORED_INIT_SIZE 10000

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

struct BFSnode{
  uint32_t nodeID;
  bool sameSCC;
};


class Graph {
private:
    int threadsNum;
    NodeIndex In; //index for incoming edges
    NodeIndex Out;//index for outcoming edges
    Buffer In_Buf;//buffer for incoming edges
    Buffer Out_Buf;//buffer for outcoming edges
    Queue<BFSnode>* ForwardFringe;
    Queue<BFSnode>* BackwardsFringe;
    Explored* ForwardExplored;
    Explored* BackwardsExplored;
    HashTable<InsEdge> duplicates{HT_GRAPH_HASH_SIZE, HT_GRAPH_BUCKET_SIZE};
    CC* cc = NULL;
    SCC* scc = NULL;
    bool opAdds = false;
    bool isDynamic = true;
    uint32_t current_version = 0;
public:
    Graph(int t);
    ~Graph();

    void createComponents();
    void rebuildCC();
    void add(uint32_t from, uint32_t to); //add a new edge
    int query(uint32_t from, uint32_t to, uint32_t version, int threadID); //search for the shortest path and return it
    bool SingleLevelBFSExpand(NodeIndex &Index, Buffer &Buff, uint32_t &neighbors, Queue<BFSnode> &Fringe, Explored &explored, Explored &Goal, uint32_t &node, bool isForward, uint32_t version);
    void printGraph(); //unit testing
    void clear(int i);
    void graphStatic(){isDynamic = false;}
    NodeIndex getIn()  { return In; }
    NodeIndex getOut() { return Out;}
    Buffer getBIn()    { return In_Buf; }
    Buffer getBOut()   { return Out_Buf;}
    void increaseVersion(){current_version++;}
    uint32_t getCurrentVersion(){return current_version;}
};

#endif
