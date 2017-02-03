#ifndef GHT_H
#define GHT_H

#include <iostream>
#include <cstdlib>
#include <cstdint>

#define HASH_ENTRIES 10067  //need a prime number
#define BUCKET_ENTRIES 20   //chosen after tests

typedef struct node {
    uint32_t from;
    uint32_t to;
    uint32_t version;
} node;

struct bucket {
    uint32_t bucket_entries; //entries of each bucket
    uint32_t offset;         //until where is the bucket full
    node* nodes;         //array of the contents of the bucket
};

class GHT {
private:
    uint32_t entries;   //number of entries
    bucket* bucketData; //buckets
public:
    GHT();  //constructor
    ~GHT(); //destructor
    int hashFunction(uint32_t from, uint32_t to);
    void add(node n);
    bool find(node n);
    void printHT(); //unit testing
    void clear();
};

#endif
