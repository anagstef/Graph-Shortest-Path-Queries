#ifndef HT_TEMPLATE_H
#define HT_TEMPLATE_H

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include "Buck_Template.h"

template <class T>
class HashTable {
private:
    int entries;
    Bucket<T>* bucketData;
public:
    HashTable(int hash_entries, int bucket_entries);
    ~HashTable();
    int hashFunction(T key);
    void add(T value);
    bool find(T value);
    void printHT();
    void clear();
};

#include "HT_Template.cpp"
#endif
