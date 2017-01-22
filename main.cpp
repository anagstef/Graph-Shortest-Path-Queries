#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <string>
#include "list_node.h"
#include "Graph.h"

using namespace std;

struct op {
    string type;
    uint32_t node1;
    uint32_t node2;
};

void create_graph(istream &input, Graph &graph) {
    string line;
    do {
        getline(input, line);
        if (line != "S" && line != "") {
            uint32_t node, neighbour;
            istringstream command(line);
            command >> node;
            command >> neighbour;
            graph.add(node, neighbour);
            // cout << "Added" << node << " " << neighbour << endl;
        }
    } while (line != "S");
}

void operations(istream &input, Graph &graph) {
    string line;

    getline(input, line);

    if (line == "STATIC"){
      graph.graphStatic();
      graph.createComponents();
    }
    else if (line == "DYNAMIC"){
      graph.createComponents();
    }
    else{
      graph.createComponents();
      input.clear();
      input.seekg(0);
      // std::cerr << "KLSPR1" << std::endl;
    }
    // graph.graphStatic();
    // graph.createComponents();
    // uint32_t gotl = 0;
    // uint32_t f = 0;
    // uint32_t q = 0;
    while (!input.eof()) {

        getline(input, line);
        string c;
        uint32_t source, dest;
        // gotl++;

        if (line == "F" || line == "STATIC"){
          graph.rebuildCC();
          // f++;
          continue;
        }

        //create prob a list to execute blocks of commands
        istringstream command(line);
        command >> c;
        command >> source;
        command >> dest;
        if (c == "A") {
            // cout << "Add" << source << "--" << dest << endl;
            graph.add(source, dest);
        }
        else if (c == "Q") {
            // cout << "Query" << source << "--" << dest << endl;
            // graph.query(source, dest);
            cout << graph.query(source, dest) << endl;
            graph.clean();
            // q++;
            // if(q>=59348)
            //   std::cerr << "Q " << source << "  " <<  dest << std::endl;
        }
        else if (c != "") {
            cout << "Unknown command" << endl;
        }

    }
    // std::cerr << gotl << std::endl;
    // std::cerr << f << std::endl;
    // std::cerr << q << std::endl;
}

int main(int argc, char const *argv[]) {
    //create_graph(cin);
    ifstream input;
    string filename;

    Graph graph;

    // if (argc == 3) {
    input.open(&argv[1][0]);
    if (!input.is_open()) {
        cout << "Couldn't open file. End of execution." << endl;
        exit(-1);
    }
    create_graph(input, graph);
    input.close();
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
    //cout << "end of insertion" << endl;
    input.open(&argv[2][0]);
    if (!input.is_open()) {
       cout << "Couldn't open file. End of execution." << endl;
       exit(-1);
    }
    operations(input, graph);
    input.close();
    // }
    return 0;
}
