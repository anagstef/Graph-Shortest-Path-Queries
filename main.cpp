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

using namespace std;

// struct op {
//     string type;
//     uint32_t node1;
//     uint32_t node2;
// };

void create_graph(FILE *fp, Graph &graph) {
    uint32_t node, neighbour;
    while(fscanf(fp, "%u  %u", &node, &neighbour) == 2){
      graph.add(node, neighbour);
    }
}

// void DynamicOperations(FILE *fp, Graph &graph, JobScheduler& JS) {
//     DynamicQueryJob* qj = new DynamicQueryJob[1000000];
//     int jCounter = 0;
//     char buff[64];
//     char op;
//     uint32_t source, dest;
//     bool read = false;
//
//     while(1){
//
//         if(!read){
//           if(fgets(buff, 64, fp) == NULL)
//             break;
//         }
//         read = false;
//         sscanf(buff, "%c %u  %u", &op, &source, &dest);
//
//         if (op == 'F'){
//
//           for(int i=0;i<jCounter; i++)
//             JS.submit_job(&(qj[i]));
//
//           JS.execute_all_jobs();
//           JS.wait_all_tasks_finish();
//           JS.printResults();
//
//           jCounter = 0;
//
//           if(fgets(buff, 64, fp) == NULL)
//             break;
//           else
//             read = true;
//
//           graph.rebuildCC();
//           continue;
//         }
//
//         if (op == 'A') {
//             graph.add(source, dest);
//         }
//         else if (op == 'Q') {
//           // qj = new QueryJob(source, dest, &graph);
//           // JS.submit_job(qj);
//           qj[jCounter].setFrom(source);
//           qj[jCounter].setTo(dest);
//           qj[jCounter].setGraph(&graph);
//           jCounter++;
//           // printf("%d\n", graph.query(source, dest));
//           // graph.clean();
//         }
//     }
//     delete[] qj;
// }

void StaticOperations(FILE *fp, Graph &graph, JobScheduler& JS) {
    StaticQueryJob* qj = new StaticQueryJob[1000000];
    int jCounter = 0;
    char buff[64];
    char op;
    uint32_t source, dest;

    while(fgets(buff, 64, fp) != NULL){

        sscanf(buff, "%c %u  %u", &op, &source, &dest);

        if (op == 'F'){

          for(int i=0;i<jCounter; i++)
            JS.submit_job(&(qj[i]));

          JS.execute_all_jobs();
          JS.wait_all_tasks_finish();
          JS.printResults();
          jCounter = 0;
        }
        else if (op == 'Q') {
          qj[jCounter].setFrom(source);
          qj[jCounter].setTo(dest);
          qj[jCounter].setGraph(&graph);
          jCounter++;
        }
        else{
          printf("Something went wrong while reading operations file!\n");
          delete[] qj;
          return;
        }
    }
    delete[] qj;
}

int main(int argc, char const *argv[]) {
    char buff[64];
    bool GraphDynamic;
    FILE *fp;
    int threads = 15;
    Graph graph(threads);
    JobScheduler JS(threads);

    fp = fopen(argv[1] , "r");
    if (fp == NULL){
      perror ("Error opening file");
      exit(-1);
    }
    create_graph(fp, graph);
    fclose(fp);
    // return 0;
    //graph.createComponents();
    // cout << "finished insertion" << endl;
    // graph.createSCComponents();
    // cout << graph.estimateShortestPathStronglyConnectedComponents(0,1) << endl;
    // cout << graph.estimateShortestPathStronglyConnectedComponents(3,10) << endl;
    //cout << graph.findNodeStronglyConnectedComponentID(1) << endl;
    // graph.destroyStronglyConnectedComponents();
    // return 0;
    // graph.printGraph();
    // cout << "end of insertion" << endl;
    fp = fopen(argv[2] , "r");
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


    StaticOperations(fp, graph, JS);

    fclose(fp);
    return 0;
}
