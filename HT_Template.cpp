#include "HT_Template.h"
#include <fstream>
#include <sstream>

using namespace std;

template <class T>
HashTable<T>::HashTable() {
    entries = HASH_ENTRIES;
    bucketData = new Bucket<T>*[entries]();
    for (int i = 0; i < entries; ++i) {
        bucketData[i] = new Bucket<T>();
    }
}

template <class T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < entries; ++i) {
        delete bucketData[i];
    }
    delete[] bucketData;
}

template <class T>
int HashTable<T>::hashFunction(T key) {
    size_t key_hash = hash<T>()(key);
    //printf("Hash value -:%lu\n", key_hash);
    return key_hash%entries;
}

template <class T>
bool HashTable<T>::find(T value) {
    int hash = hashFunction(value);
    T* nodes = bucketData[hash]->getNodes();
    int offset = bucketData[hash]->getOffset();
    for (int i = 0; i < offset; ++i) {
        if (nodes[i] == value) return true;
    }
    return false;
}

template <class T>
void HashTable<T>::add(T value) {
    int hash = hashFunction(value);
    if (find(value)) return;
    bucketData[hash]->add(value);
}

template <class T>
void HashTable<T>::printHT() {
    for (int i = 0; i < entries; ++i) {
        T* nodes = bucketData[i]->getNodes();
        int offset = bucketData[i]->getOffset();
        if (offset > 0) {
            cout << "bucket -: " << i << " offset -:" << offset << endl;
            for (int j = 0; j < offset; ++j) {
                printf("%u, ", nodes[j]);
            }
            cout << endl;
        }
    }
}

/*int main(void) {
    HashTable<uint32_t> ht;
    ifstream input;
    input.open("smallGraph.txt");
    string line;
    if (input.is_open()) {
        do {
            getline(input, line);
            if (line != "S") {
                uint32_t node, neighbour;
                istringstream command(line);
                command >> node;
                command >> neighbour;
                ht.add(node);
                ht.add(neighbour);
            }
        } while (line != "S");
        input.close();
    }
    ht.printHT();
}*/
