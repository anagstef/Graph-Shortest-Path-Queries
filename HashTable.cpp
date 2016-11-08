#include "HashTable.h"
#include <fstream>
#include <sstream>

using namespace std;

/*void Bucket::insert(uint32_t value) {
    if (offset == bucket_entries) {
        bucket_entries = bucket_entries*2;
        nodes = (uint32_t*) realloc(nodes, bucket_entries * sizeof(uint32_t));
    }
    nodes[offset] = value;
    offset++;
}
*/

HashTable::HashTable() {
    entries = HASH_ENTRIES;
    bucketData = (Bucket*) malloc(HASH_ENTRIES * sizeof(Bucket));
    for (uint32_t i = 0; i < entries; ++i) {
        bucketData[i].nodes = (uint32_t*) malloc(sizeof(uint32_t) * BUCKET_ENTRIES);
        bucketData[i].bucket_entries = BUCKET_ENTRIES;
        bucketData[i].offset = 0;
    }
}

HashTable::~HashTable() {
    for (uint32_t i = 0; i < entries; ++i) {
        free(bucketData[i].nodes);
    }
    free(bucketData);
}

uint32_t HashTable::hashFunction(uint32_t value) {
    return value%entries;
}

void HashTable::add(uint32_t value) {
    uint32_t hash = hashFunction(value);
    if (find(value)) return;
    if (bucketData[hash].offset == bucketData[hash].bucket_entries) {
        bucketData[hash].bucket_entries = bucketData[hash].bucket_entries*2;
        bucketData[hash].nodes = (uint32_t*) realloc(bucketData[hash].nodes,
        bucketData[hash].bucket_entries * sizeof(uint32_t));
    }
    bucketData[hash].nodes[bucketData[hash].offset] = value;
    bucketData[hash].offset++;
}

bool HashTable::find(uint32_t value) {
    uint32_t hash = hashFunction(value);
    for (uint32_t i = 0; i < bucketData[hash].offset; ++i) {
        if (bucketData[hash].nodes[i] == value) return true;
    }
    return false;
}

void HashTable::printHT() {
    for (uint32_t i = 0; i < entries; i++) {
        cout << "bucket: " << i << endl;
        for (uint32_t j = 0; j < bucketData[i].offset; j++) {
            printf("%d, ", bucketData[i].nodes[j]);
        }
        cout << endl;
    }
}

int main(void) {
    HashTable ht;
    //ht.init();
    ifstream input;
    input.open("mediumGraph.txt");
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
    //ht.printHT();
}
