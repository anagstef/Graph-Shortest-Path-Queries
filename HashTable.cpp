#include "HashTable.h"
#include <fstream>
#include <sstream>

using namespace std;

HashTable::HashTable() {
    entries = HASH_ENTRIES;
    bucketData = (Bucket*) malloc(HASH_ENTRIES * sizeof(Bucket)); //allocate every bucket
    for (uint32_t i = 0; i < entries; ++i) {
        bucketData[i].nodes = (uint32_t*) malloc(sizeof(uint32_t) * BUCKET_ENTRIES); //allocate the array data
        bucketData[i].bucket_entries = BUCKET_ENTRIES; //set the entries
        bucketData[i].offset = 0; //set the offset
    }
}

HashTable::~HashTable() {
    for (uint32_t i = 0; i < entries; ++i) {
        free(bucketData[i].nodes); //free the arrays
    }
    free(bucketData); //free the hashtable
}

uint32_t HashTable::hashFunction(uint32_t value) {
    return value%entries; //where each value hashes
}

void HashTable::add(uint32_t value) {
    uint32_t hash = hashFunction(value); //find the bucket
    if (find(value)) return; //if the value exists don't add
    if (bucketData[hash].offset == bucketData[hash].bucket_entries) { //if the bucket is full
        bucketData[hash].bucket_entries = bucketData[hash].bucket_entries*2; //double the bucket size
        bucketData[hash].nodes = (uint32_t*) realloc(bucketData[hash].nodes, bucketData[hash].bucket_entries * sizeof(uint32_t)); //realloc the bucket
    }
    bucketData[hash].nodes[bucketData[hash].offset] = value; //insert the value
    bucketData[hash].offset++; //increase the offset to know where to insert
}

bool HashTable::find(uint32_t value) {
    uint32_t hash = hashFunction(value); //go to the correct bucket
    for (uint32_t i = 0; i < bucketData[hash].offset; ++i) { //go through the bucket until offset
        if (bucketData[hash].nodes[i] == value) return true; //return true if node value == value
    }
    return false;
}

void HashTable::printHT() { //simple printing function
    for (uint32_t i = 0; i < entries; i++) {
        cout << "bucket: " << i << endl;
        for (uint32_t j = 0; j < bucketData[i].offset; j++) {
            printf("%d, ", bucketData[i].nodes[j]);
        }
        cout << endl;
    }
}

/*int main(void) {
    HashTable ht;
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
    ht.printHT();
}
 */
