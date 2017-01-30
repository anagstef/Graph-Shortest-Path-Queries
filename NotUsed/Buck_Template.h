#ifndef HT_BUCKETT_H
#define HT_BUCKETT_H

#include <iostream>
#include <cstdlib>

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

#include "Buck_Template.cpp"
#endif
