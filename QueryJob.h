#ifndef QUERYJOB_H
#define QUERYJOB_H

#include "Job.h"
#include "Graph.h"

class QueryJob : public Job{
private:
  uint32_t from;
  uint32_t to;
  Graph* graph;

public:
  QueryJob(uint32_t f, uint32_t t, Graph* g){from=f; to=t; graph=g;}
  ~QueryJob(){}
  void execute(int threadID){
    result = graph->query(from, to, threadID);
    graph->clear(threadID);
  }
  void setFrom(uint32_t f){from=f;}
  void setTo(uint32_t t){to=t;}
  void setGraph(Graph* g){graph=g;}

};

#endif
