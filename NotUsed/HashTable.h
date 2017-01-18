#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <cstdint>

//10067
#define HASH_ENTRIES 10067  //need a prime number
#define BUCKET_ENTRIES 20   //chosen after tests

struct Bucket {
    uint32_t bucket_entries; //entries of each bucket
    uint32_t offset;         //until where is the bucket full
    uint32_t* nodes;         //array of the contents of the bucket
};

class HashTable {
private:
    uint32_t entries;   //number of entries
    Bucket* bucketData; //buckets
public:
    HashTable();  //constructor
    ~HashTable(); //destructor
    uint32_t hashFunction(uint32_t value); //simple modulo
    void add(uint32_t value); //insert a value into hash table
    bool find(uint32_t value); //search if the value already exists
    void printHT(); //unit testing
    void clear();
};

#endif
