#ifndef STATICQUERYJOB_H
#define STATICQUERYJOB_H

#include "Job.h"
#include "Graph.h"

class StaticQueryJob : public Job{
private:
  uint32_t from;
  uint32_t to;
  Graph* graph;

public:
  StaticQueryJob(){}
  StaticQueryJob(uint32_t f, uint32_t t, Graph* g){from=f; to=t; graph=g;}
  ~StaticQueryJob(){}
  void execute(int threadID){
    result = graph->query(from, to, 0, threadID);
    graph->clear(threadID);
  }
  void setFrom(uint32_t f){from=f;}
  void setTo(uint32_t t){to=t;}
  void setGraph(Graph* g){graph=g;}

};

#endif
