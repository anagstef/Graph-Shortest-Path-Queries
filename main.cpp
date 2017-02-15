#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <cstring>
#include "list_node.h"
#include "Graph.h"
#include "JobScheduler.h"
#include "StaticQueryJob.h"
#include "DynamicQueryJob.h"

using namespace std;

#define QUERYJOB_QUEUE 1000000


void create_graph(FILE *fp, Graph &graph) {
    uint32_t node, neighbour;
    while(fscanf(fp, "%u  %u", &node, &neighbour) == 2){
      graph.add(node, neighbour);
    }
}

void DynamicOperations(FILE *fp, Graph &graph, JobScheduler& JS) {
  int real_size = QUERYJOB_QUEUE;
  DynamicQueryJob* qj = (DynamicQueryJob*) malloc(sizeof(DynamicQueryJob) * real_size);
  int jCounter = 0;
  char buff[64];
  char op;
  uint32_t source, dest;
  bool read = false;
  bool lastCommandQ = false;
  while(1){

        if(!read){
          if(fgets(buff, 64, fp) == NULL)
            break;
        }
        read = false;
        sscanf(buff, "%c %u  %u", &op, &source, &dest);

        if (op == 'F'){

          for(int i=0;i<jCounter; i++)
            JS.submit_job(qj + i);

          JS.execute_all_jobs();
          JS.wait_all_tasks_finish();
          JS.printResults();

          jCounter = 0;

          //if this is the end of file, there is no need for rebuild
          if(fgets(buff, 64, fp) == NULL)
            break;
          else
            read = true;

          // cerr << "before rebuildCC" << endl;
          graph.rebuildCC();
          // cerr << "after rebuildCC" << endl;
          lastCommandQ = false;
        }
        else if (op == 'A') {
          if(lastCommandQ){
            graph.increaseVersion();
          }


          graph.add(source, dest);
          lastCommandQ = false;
        }
        else if (op == 'Q') {
          if(jCounter == real_size){
            real_size *= 2;
            qj = (DynamicQueryJob*) realloc(qj, sizeof(DynamicQueryJob) * real_size);
          }
          new (&qj[jCounter]) DynamicQueryJob(source, dest, &graph, graph.getCurrentVersion());
          jCounter++;
          lastCommandQ = true;
        }
        else{
          printf("Something went wrong while reading operations file!\n");
          free(qj);
          return;
        }
    }
    free(qj);
}

void StaticOperations(FILE *fp, Graph &graph, JobScheduler& JS) {
    int real_size = QUERYJOB_QUEUE;
    StaticQueryJob* qj = (StaticQueryJob*) malloc(sizeof(StaticQueryJob) * real_size);
    int jCounter = 0;
    char buff[64];
    char op;
    uint32_t source, dest;

    while(fgets(buff, 64, fp) != NULL){

        sscanf(buff, "%c %u  %u", &op, &source, &dest);

        if (op == 'F'){

          for(int i=0;i<jCounter; i++)
            JS.submit_job(qj + i);

          JS.execute_all_jobs();
          JS.wait_all_tasks_finish();
          JS.printResults();
          jCounter = 0;
        }
        else if (op == 'Q') {
          if(jCounter == real_size){
            real_size *= 2;
            qj = (StaticQueryJob*) realloc(qj, sizeof(StaticQueryJob) * real_size);
          }
          new (&qj[jCounter]) StaticQueryJob(source, dest, &graph);
          jCounter++;
        }
        else{
          printf("Something went wrong while reading operations file!\n");
          free(qj);
          return;
        }
    }
    free(qj);
}

int main(int argc, char const *argv[]) {
    char buff[64];
    bool GraphDynamic;
    FILE *fp;
    int threads;

    if(argc != 4){
      perror ("Invalid number of arguments!");
      exit(-1);
    }
    threads = atoi(argv[1]);
    if(threads < 1){
      perror ("Invalid number of threads!");
      exit(-1);
    }

    Graph graph(threads);
    JobScheduler JS(threads);

    fp = fopen(argv[2] , "r");
    if (fp == NULL){
      perror ("Error opening file");
      exit(-1);
    }
    create_graph(fp, graph);
    fclose(fp);

    fp = fopen(argv[3] , "r");
    if (fp == NULL){
      perror ("Error opening file");
      exit(-1);
    }

    //read first line to check if it's static or dynamic graph
    fgets(buff, 64, fp);
    if (strcmp(buff, "STATIC\n") == 0){
      graph.graphStatic();
      graph.createComponents();
      GraphDynamic = false;
    }
    else if (strcmp(buff, "DYNAMIC\n") == 0){
      graph.createComponents();
      GraphDynamic = true;
    }
    else{
      graph.createComponents();
      rewind(fp);
      GraphDynamic = true;
    }

    if(GraphDynamic)
      DynamicOperations(fp, graph, JS);
    else
      StaticOperations(fp, graph, JS);

    fclose(fp);
    JS.exitThreads();
    return 0;
}
