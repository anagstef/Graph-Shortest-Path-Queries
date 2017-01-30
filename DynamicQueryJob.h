#ifndef DYNAMICQUERYJOB_H
#define DYNAMICQUERYJOB_H

#include "Job.h"
#include "Graph.h"

class DynamicQueryJob : public Job{
private:
  uint32_t from;
  uint32_t to;
  Graph* graph;
  uint32_t version;

public:
  DynamicQueryJob(){}
  DynamicQueryJob(uint32_t f, uint32_t t, Graph* g, uint32_t v)
  {from=f; to=t; graph=g; version=v;}
  ~DynamicQueryJob(){}
  void execute(int threadID){
    result = graph->query(from, to, version, threadID);
    graph->clear(threadID);
  }
  void setFrom(uint32_t f){from=f;}
  void setTo(uint32_t t){to=t;}
  void setGraph(Graph* g){graph=g;}
  void setVersion(uint32_t v){version=v;}

};

#endif
