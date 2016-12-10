#ifndef HT_TEMPLATE_H
#define HT_TEMPLATE_H

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include "Buck_Template.h"

#define HASH_ENTRIES 10067  //need a prime number
#define BUCKET_ENTRIES 20   //chosen after tests

template <class T>
class HashTable {
private:
    int entries;
    Bucket<T>* bucketData;
public:
    HashTable();
    ~HashTable();
    int hashFunction(T key);
    void add(T value);
    bool find(T value);
    void printHT();
};

#include "HT_Template.cpp"
#endif
