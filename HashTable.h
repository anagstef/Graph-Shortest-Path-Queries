#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <cstdint>

#define HASH_ENTRIES 8599
#define BUCKET_ENTRIES 200

class HashTable {
private:
    uint32_t entries;
    uint32_t bucket_entries;
    uint32_t** bucketData;
public:
    HashTable();
    ~HashTable();
    uint32_t hashFunction(uint32_t value);
    void add(uint32_t key);
    void printHT();
};

#endif
