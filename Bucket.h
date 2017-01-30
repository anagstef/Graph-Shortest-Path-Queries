#ifndef BUCKET_H
#define BUCKET_H

#include <iostream>
#include <cstdlib>
#include <cstdint>

using namespace std;

//---------------BUCKET---------------//

template <class T>
class Bucket {
private:
    int bucket_entries;
    int offset;
    T* nodes;
public:
    Bucket(int init_size);
    ~Bucket();
    void add(T value);
    void clear();
    T* getNodes() {return nodes;}
    int getOffset() {return offset;}
    void setOffset(int o) {offset = o;}
};

//---------------END OF BUCKET---------------//

//---------------BUCKET---------------//

template <class T>
Bucket<T>::Bucket(int init_size) {
    bucket_entries = init_size;
    nodes = (T*)malloc(bucket_entries * sizeof(T));
    offset = 0;
}

template <class T>
Bucket<T>::~Bucket() {
    free(nodes);
}

template <class T>
void Bucket<T>::add(T value) {
    if (offset == bucket_entries) {
        bucket_entries = 2*bucket_entries;
        nodes = (T*)realloc(nodes, bucket_entries * sizeof(T));
    }
    nodes[offset] = value;
    offset++;
}

template <class T>
void Bucket<T>::clear() {
    offset = 0;
}

//---------------END OF BUCKET---------------//

#endif
