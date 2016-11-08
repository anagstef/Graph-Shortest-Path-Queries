#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <cstdint>

#define HASH_ENTRIES 10067
#define BUCKET_ENTRIES 50

struct Bucket {
    uint32_t bucket_entries;
    uint32_t offset;
    uint32_t* nodes;
    void insert(uint32_t value);
};

class HashTable {
private:
    uint32_t entries;
    Bucket* bucketData;
public:
    HashTable();
    ~HashTable();
    void init();
    uint32_t hashFunction(uint32_t value);
    void add(uint32_t value);
    bool find(uint32_t value);
    void printHT();
};

#endif
