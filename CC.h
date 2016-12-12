#ifndef CC_H
#define CC_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include "NodeIndex.h"
#include "UpdateIndex.h"

#define METRIC 0.32

class UpdateIndex;

class CC{
private:
  uint32_t* ccindex;
  uint32_t indexsize;
  UpdateIndex* updateIndex;
  uint32_t componentCount;
  uint32_t QueryNum;
  uint32_t UpdateUsed;
  Queue<uint32_t>* queue;
  uint32_t offset;
public:
  CC(NodeIndex& In, NodeIndex& Out, Buffer& In_Buf, Buffer& Out_Buf);
  ~CC();

  void CC_BFS(NodeIndex& In, NodeIndex& Out, Buffer& In_Buf, Buffer& Out_Buf);
  bool insertNewEdge(uint32_t nodeIdS, uint32_t nodeIdE);
  bool areNodesConnected(uint32_t nodeIdS, uint32_t nodeIdE);
  bool rebuildIndexes();
  void increaseQueryNum();
};

#endif
