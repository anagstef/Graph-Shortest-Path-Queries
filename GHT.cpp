#include "GHT.h"

using namespace std;

#include "GHT.h"
#include <fstream>
#include <sstream>

using namespace std;

GHT::GHT() {
    entries = HASH_ENTRIES;
    bucketData = (bucket*) malloc(HASH_ENTRIES * sizeof(bucket)); //allocate every bucket
    for (uint32_t i = 0; i < entries; ++i) {
        bucketData[i].nodes = (node*) malloc(sizeof(node) * BUCKET_ENTRIES); //allocate the array data
        bucketData[i].bucket_entries = BUCKET_ENTRIES; //set the entries
        bucketData[i].offset = 0; //set the offset
    }
}

GHT::~GHT() {
    for (uint32_t i = 0; i < entries; ++i) {
        free(bucketData[i].nodes); //free the arrays
    }
    free(bucketData); //free the hashtable
}

int GHT::hashFunction(uint32_t from, uint32_t to) {
    return (from+to)%entries; //where each value hashes
}

void GHT::add(uint32_t from, uint32_t to, uint32_t version) {
    int hash = hashFunction(from, to); //find the bucket
    if (find(from,to,version)) return; //if the value exists don't add
    if (bucketData[hash].offset == bucketData[hash].bucket_entries) { //if the bucket is full
        bucketData[hash].bucket_entries = bucketData[hash].bucket_entries*2; //double the bucket size
        bucketData[hash].nodes = (node*) realloc(bucketData[hash].nodes, bucketData[hash].bucket_entries * sizeof(node)); //realloc the bucket
    }
    bucketData[hash].nodes[bucketData[hash].offset].from = from; //insert the value
    bucketData[hash].nodes[bucketData[hash].offset].to = to;
    bucketData[hash].nodes[bucketData[hash].offset].version = version;
    bucketData[hash].offset++; //increase the offset to know where to insert
}

bool GHT::find(uint32_t from, uint32_t to, uint32_t version) {
    int hash = hashFunction(from, to); //go to the correct bucket
    for (uint32_t i = 0; i < bucketData[hash].offset; ++i) { //go through the bucket until offset
        if (bucketData[hash].nodes[i].from == from && bucketData[hash].nodes[i].to == to && bucketData[hash].nodes[i].version < version) return true; //return true if node value == value
    }
    return false;
}

void GHT::clear() {
    for (uint32_t i = 0; i < entries; ++i) {
        bucketData[i].offset = 0;
    }
}

void GHT::printHT() { //simple printing function
    for (uint32_t i = 0; i < entries; i++) {
        cout << "bucket: " << i << endl;
        for (uint32_t j = 0; j < bucketData[i].offset; j++) {
            printf("%d, ", bucketData[i].nodes[j].from);
        }
        cout << endl;
    }
}
