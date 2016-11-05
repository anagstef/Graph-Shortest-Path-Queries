#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <string>
#include "list_node.h"
#include "list.h"

using namespace std;

void create_graph(istream &input) {
    string line;
    do {
        getline(input, line);
        if (line != "S") {
            uint32_t node, neighbour;
            istringstream command(line);
            command >> node;
            command >> neighbour;
            cout << node << " " << neighbour << endl;
            list_node* lnode = new list_node();
            lnode->print_node();
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

    if (argc == 2) {
        input.open(&argv[1][0]);
        if (!input.is_open()) {
            cout << "Couldn't open file. End of execution." << endl;
            exit(-1);
        }
        create_graph(input);
    }

    cout << "Please give the operations file name" << endl;
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
    }

    list l;
    cout << l.is_empty() << endl;
    node* n1 = new node(10);
    node* n2 = new node(20);
    node* n3 = new node(30);
    node* n4 = new node(40);
    node* n5 = new node(50);
    l.push(*n1);
    l.push(*n2);
    l.push(*n3);
    l.push(*n4);
    l.push(*n5);
    cout << l.is_empty() << endl;
    l.print_list();
    cout << l.search(10) << endl;
    return 0;
}
