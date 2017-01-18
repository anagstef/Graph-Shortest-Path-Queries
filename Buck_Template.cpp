#include "Buck_Template.h"

using namespace std;

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
    // bucket_entries = BUCKET_ENTRIES;
    // nodes = (T*)realloc(nodes, bucket_entries * sizeof(T));
    offset = 0;
}
