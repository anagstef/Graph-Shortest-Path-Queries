#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <cstdint>

//10067
#define HASH_ENTRIES 500
#define BUCKET_ENTRIES 15

struct Bucket {
    uint32_t bucket_entries;
    uint32_t offset;
    uint32_t* nodes;
};

class HashTable {
private:
    uint32_t entries;
    Bucket* bucketData;
public:
    HashTable();
    ~HashTable();
    uint32_t hashFunction(uint32_t value);
    void add(uint32_t value);
    bool find(uint32_t value);
    void printHT();
};

#endif
