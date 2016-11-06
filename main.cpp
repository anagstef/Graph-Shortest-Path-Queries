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

void create_graph(istream &input, Graph &graph) {
    string line;
    do {
        getline(input, line);
        if (line != "S") {
            uint32_t node, neighbour;
            istringstream command(line);
            command >> node;
            command >> neighbour;
            graph.add(node, neighbour);
        }
    } while (line != "S");
}

void operations(istream &input) {
    string line;
    while (!input.eof()) {
        getline(input, line);
        string c;
        uint32_t source, dest;
        if (line != "F") {
            //create prob a list to execute blocks of commands
            istringstream command(line);
            command >> c;
            command >> source;
            command >> dest;
            if (c == "A") {
                cout << "Add" << endl;
            }
            else if (c == "Q") {
                cout << "Query" << endl;
            }
            else if (c != "") {
                cout << "Unknown command" << endl;
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    //create_graph(cin);
    ifstream input;
    string filename;

    Graph graph;

    if (argc == 2) {
        input.open(&argv[1][0]);
        if (!input.is_open()) {
            cout << "Couldn't open file. End of execution." << endl;
            exit(-1);
        }
        create_graph(input, graph);
    }

    /*cout << "Please give the operations file name" << endl;
    const char* file;
    getline(cin, filename);
    file = filename.c_str();
    input.open(file);
    if (input.is_open()) {
        operations(input);
        input.close();
    }
    else {
        cout << "Wrong operations file, end of execution" << endl;
        exit(1);
    }*/
    return 0;
}
