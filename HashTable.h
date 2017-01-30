#ifndef HT_H
#define HT_H

#include <iostream>
#include <cstdlib>
#include <cstdint>

#include "Bucket.h"

using namespace std;

//---------------HASH TABLE---------------//

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

//---------------END OF HASH TABLE---------------//

//---------------HASH TABLE---------------//

template <class T>
HashTable<T>::HashTable(int hash_entries, int bucket_entries) {
    entries = hash_entries;
    bucketData = (Bucket<T>*) malloc(sizeof(Bucket<T>) * entries);
    for (int i = 0; i < entries; ++i) {
        new (&bucketData[i]) Bucket<T>(bucket_entries);
    }
}

template <class T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < entries; ++i) {
        bucketData[i].~Bucket();
    }
    free(bucketData);
}

template <class T>
int HashTable<T>::hashFunction(T key) {
    return key%entries;
}

template <class T>
bool HashTable<T>::find(T value) {
    int hash = hashFunction(value);
    T* nodes = bucketData[hash].getNodes();
    int offset = bucketData[hash].getOffset();
    for (int i = 0; i < offset; ++i) {
        if (nodes[i] == value) return true;
    }
    return false;
}

template <class T>
void HashTable<T>::add(T value) {
    int hash = hashFunction(value);
    bucketData[hash].add(value);
}

template <class T>
void HashTable<T>::clear() {
    for (int i = 0; i < entries; ++i) {
        bucketData[i].setOffset(0);
    }
}

template <class T>
void HashTable<T>::printHT() {
    for (int i = 0; i < entries; ++i) {
        T* nodes = bucketData[i].getNodes();
        int offset = bucketData[i].getOffset();
        if (offset > 0) {
            cout << "bucket -: " << i << " offset -:" << offset << endl;
            for (int j = 0; j < offset; ++j) {
                printf("%u, ", nodes[j]);
            }
            cout << endl;
        }
    }
}

//---------------END OF HASH TABLE---------------//

#endif
