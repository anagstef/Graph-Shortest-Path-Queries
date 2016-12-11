#ifndef CC_H
#define CC_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include "Graph.h"


class CC{
private:
  uint32_t* ccindex;
  uint32_t indexsize;
  UpdateIndex* UpdateIndex;
  uint32_t metricVal;
  uint32_t componentCount;
  uint32_t offset;
  Graph* graph;
  Queue<uint32_t> queue;
public:
  CC(Graph& graph);
  ~CC();

  void CC_BFS();
  bool insertNewEdge(uint32_t nodeIdS, uint32_t nodeIdE);
  int findNodeConnectedComponentID(uint32_t nodeId);
  bool rebuildIndexes();
};

#endif
