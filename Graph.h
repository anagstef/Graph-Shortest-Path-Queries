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

class CC;

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
    Queue<uint32_t> ForwardFringe;
    Queue<uint32_t> BackwardsFringe;
    Explored ForwardExplored;
    Explored BackwardsExplored;
    HashTable<InsEdge> duplicates;
    CC* cc;
    bool opAdds = false;
    bool isDynamic;
public:

    void createComponents();
    void rebuildCC();
    void add(uint32_t from, uint32_t to); //add a new edge
    int query(uint32_t from, uint32_t to); //search for the shortest path and return it
    void printGraph(); //unit testing
    void clean();
    NodeIndex getIn() {return In;}
    NodeIndex getOut() {return Out;}
};

#endif
