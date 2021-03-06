#ifndef CC_H
#define CC_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include "NodeIndex.h"
#include "UpdateIndex.h"
#include "Templates.h"

#define METRIC 0.52
#define CC_QUEUE_INIT_SIZE 10000

class UpdateIndex;

class CC{
private:
  uint32_t* ccindex;
  uint32_t indexsize;
  UpdateIndex* updateIndex;
  uint32_t componentCount;
  uint32_t QueryNum;
  uint32_t UpdateUsed;
  Queue<uint32_t> queue{CC_QUEUE_INIT_SIZE};
  uint32_t offset;
  NodeIndex* In;
  NodeIndex* Out;
  Buffer* In_Buf;
  Buffer* Out_Buf;
  pthread_mutex_t UpdateUsed_mtx;
  pthread_mutex_t QueryNum_mtx;
public:
  CC(NodeIndex& In, NodeIndex& Out, Buffer& In_Buf, Buffer& Out_Buf);
  ~CC();

  void estimateConnectedComponents();
  void CC_BFS();
  bool insertNewEdge(uint32_t nodeIdS, uint32_t nodeIdE, uint32_t version);
  bool areNodesConnected(uint32_t nodeIdS, uint32_t nodeIdE, uint32_t version);
  bool rebuildIndexes();
  void increaseQueryNum();
};

#endif
