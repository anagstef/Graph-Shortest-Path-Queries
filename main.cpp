#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <string>
#include "list_node.h"
#include "Graph.h"
// #include "HashTable.h"

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
    if (line == "STATIC") {
        graph.createSCComponents();
        while (!input.eof()) {
            getline(input, line);
            string c;
            uint32_t source, dest;
            if (line == "F"){
              continue;
            }
            istringstream command(line);
            command >> c;
            command >> source;
            command >> dest;
            if (c == "Q") {
                cout << graph.query(source, dest) << endl;
                graph.clean();
            }
            else if (c != "") {
                cout << "Unknown command" << endl;
            }
        }
    }
    else if (line == "DYNAMIC") {
        graph.createComponents();
        while (!input.eof()) {
            getline(input, line);
            string c;
            uint32_t source, dest;
            if (line == "F") {
                graph.rebuildCC();
                continue;
            }
            istringstream command(line);
            command >> c;
            command >> source;
            command >> dest;
            if (c == "Q") {
                cout << graph.query(source, dest) << endl;
                graph.clean();
            }
            if (c == "A") {
                graph.add(source, dest);
            }
            else if (c != "") {
                cout << "Unknown command" << endl;
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    ifstream input;
    string filename;
    Graph graph;
    input.open(&argv[1][0]);
    if (!input.is_open()) {
        cout << "Couldn't open file. End of execution." << endl;
        exit(-1);
    }
    create_graph(input, graph);
    input.close();
    input.open(&argv[2][0]);
    if (!input.is_open()) {
        cout << "Couldn't open file. End of execution." << endl;
        exit(-1);
    }
    operations(input, graph);
    input.close();
    return 0;
}
