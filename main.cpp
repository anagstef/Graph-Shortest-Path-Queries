//
// Created by helena on 4/11/2016.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include "list_node.h"

using namespace std;

void create_graph(istream &input) {
    string line;
    do {
        getline(input, line);
        if (line != "S") {
            int node, neighbour;
            istringstream command(line);
            command >> node;
            command >> neighbour;
            cout << node << " " << neighbour << endl;
            list_node* lnode = new list_node(node);
            lnode->print_node();
        }
    } while (line != "S");
}

void operations(istream &input) {
    string line;
    while (!input.eof()) {
        getline(input, line);
        string c;
        int source, dest;
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
    const char* file;
    cout << "Please give the graph file name" << endl;
    getline(cin, filename);
    file = filename.c_str();
    input.open(file);
    if (input.is_open()) {
        create_graph(input);
        input.close();
    }
    else {
        cout << "Wrong operations file, end of execution" << endl;
        exit(1);
    }
    cout << "Please give the operations file name" << endl;
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
    }
    return 0;
}
