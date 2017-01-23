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

using namespace std;

struct op {
    string type;
    uint32_t node1;
    uint32_t node2;
};

void create_graph(FILE *fp, Graph &graph) {
    uint32_t node, neighbour;
    while(fscanf(fp, "%u  %u", &node, &neighbour) == 2){
      graph.add(node, neighbour);
    }
}

void operations(FILE *fp, Graph &graph) {
    char buff[64];
    char op;
    uint32_t source, dest;

    fgets(buff, 64, fp);

    if (strcmp(buff, "STATIC\n") == 0){
      graph.graphStatic();
      graph.createComponents();
    }
    else if (strcmp(buff, "DYNAMIC\n") == 0){
      graph.createComponents();
    }
    else{
      graph.createComponents();
      rewind(fp);
    }
    bool read = false;
    // while(fgets(buff, 64, fp) != NULL){
      while(1){

        if(!read){
          if(fgets(buff, 64, fp) == NULL)
            break;
        }
        read = false;
        sscanf(buff, "%c %u  %u", &op, &source, &dest);

        if (op == 'F'){
          if(fgets(buff, 64, fp) == NULL)
            break;
          else
            read = true;
          graph.rebuildCC();
          continue;
        }

        if (op == 'A') {
            graph.add(source, dest);
        }
        else if (op == 'Q') {
          printf("%d\n", graph.query(source, dest));
          graph.clean();
        }
    }
}

int main(int argc, char const *argv[]) {
    FILE *fp;
    Graph graph;

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
    operations(fp, graph);
    fclose(fp);

    return 0;
}
