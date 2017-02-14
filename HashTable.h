#ifndef HT_H
#define HT_H

#include <iostream>
#include <cstdlib>
#include <cstdint>

#include "Bucket.h"

using namespace std;

//---------------INS EDGE---------------//

struct InsEdge{
  uint32_t from;
  uint32_t to;
  int operator%(const int& a) const{
    return (from + to)%a;
  }
  bool operator==(const InsEdge& a) const{
    if (a.from == from && a.to == to)
      return true;
    else
      return false;
  }
};

//------------END OF INS EDGE-------------//

//---------------HASH TABLE---------------//

template <class T>
class HashTable {
private:
    int entries;
    Bucket<T>* bucketData;
    // size_t sizzz;
    // uint32_t num = 0;
public:
    HashTable(int hash_entries, int bucket_entries);
    ~HashTable();
    int hashFunction(T key);
    void add(T value);
    bool find(T value);
    void printHT();
    void clear();
    // void printSize(){cerr << "Sizeof(T): " << sizeof(T) << ", Number: " << num << ", Total size alloc'd in Bytes: " << sizzz << endl;}
};

//---------------END OF HASH TABLE---------------//

//---------------HASH TABLE---------------//

template <class T>
HashTable<T>::HashTable(int hash_entries, int bucket_entries) {
    entries = hash_entries;
    // sizzz = entries * bucket_entries * sizeof(T);
    // cerr << sizeof(Bucket<T>) << endl;
    // cerr << sizzz << endl;

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
    // num++;
    int hash = hashFunction(value);
    bucketData[hash].add(value);
    // sizzz += bucketData[hash].add(value);
}

template <class T>
void HashTable<T>::clear() {
    for (int i = 0; i < entries; ++i) {
        bucketData[i].setOffset(0);
    }
}

template <class T>
void HashTable<T>::printHT() {
    if (std::is_same<T, uint32_t>::value) {
        for (int i = 0; i < entries; ++i) {
            T* nodes = bucketData[i].getNodes();
            int offset = bucketData[i].getOffset();
            if (offset > 0) {
                printf("bucket -: %u offset -: %u\n", i, offset);
                for (int j = 0; j < offset; ++j) {
                    printf("%u, ", nodes[j]);
                }
                printf("\n");
            }
        }
        return;
    }
    if (std::is_same<T, InsEdge>::value) {
        for (int i = 0; i < entries; ++i) {
            T* nodes = bucketData[i].getNodes();
            int offset = bucketData[i].getOffset();
            if (offset > 0) {
                printf("bucket -: %u offset -: %u\n", i, offset);
                for (int j = 0; j < offset; ++j) {
                    printf("from: %u to: %u, ", nodes[j].from, nodes[j].to);
                }
                printf("\n");
            }
        }
        return;
    }
}

//---------------END OF HASH TABLE---------------//

#endif
