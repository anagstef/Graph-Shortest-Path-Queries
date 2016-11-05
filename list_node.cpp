#include "list_node.h"

using namespace std;

list_node::list_node() {
    length = 0;
    hasNext = false;
}

void list_node::print_node() {
    int i;
    cout << "Neigbors: " << endl;
    for (i = 0; i < length; ++i) {
        cout << i << " " << neighbor[i] << endl;
    }
    cout << "Edges: " << endl;
    for (i = 0; i < length; ++i) {
        cout << i << " " << edgeProperty[i] << endl;
    }
    if (hasNext) {
        cout << "Next: " << nextNode << endl;
    }
}
