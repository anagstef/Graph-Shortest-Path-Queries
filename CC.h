#ifndef CC_H
#define CC_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include "Graph.h"

#define METRIC 0.7

class CC{
private:
  uint32_t* ccindex;
  uint32_t indexsize;
  UpdateIndex* UpdateIndex;
  uint32_t componentCount;
  uint32_t QueryNum;
  uint32_t UpdateUsed;
  Queue<uint32_t>* queue;
  uint32_t offset;
  Graph* graph;
public:
  CC(Graph& g);
  ~CC();

  void CC_BFS();
  bool insertNewEdge(uint32_t nodeIdS, uint32_t nodeIdE);
  bool areNodesConnected(uint32_t nodeIdS, uint32_t nodeIdE);
  bool rebuildIndexes();
  void increaseQueryNum();
};

#endif
