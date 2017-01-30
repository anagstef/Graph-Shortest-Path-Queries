#ifndef UPDATEINDEX_H
#define UPDATEINDEX_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include "Graph.h"
#include "Templates.h"

#define CELL_SIZE 10
#define HT_UI_HASH_SIZE 500009
#define HT_UI_BUCKET_SIZE 10

struct UIndexCell{
  uint32_t* components;
  uint32_t size;
  uint32_t actual_size;
};

struct UpdateIndexEdge{
  uint32_t from;
  uint32_t to;
  uint32_t version;
  UpdateIndexEdge& operator=(const UpdateIndexEdge& other){
    from = other.from;
    to = other.to;
    version = other.version;
    return *this;
  }
  int operator%(const int& a){
    return (from + to)%a;
  }
  bool operator==(const UpdateIndexEdge& a){
    return (a.from == from && a.to == to && a.version <= version);
  }
};

struct InsEdge;

class UpdateIndex{
private:
  HashTable<UpdateIndexEdge> quickFind{HT_UI_HASH_SIZE, HT_UI_BUCKET_SIZE};
  UIndexCell* uindex;
  uint32_t size;
public:
  UpdateIndex(uint32_t starting_size);
  ~UpdateIndex();

  void clear();
  void increaseCapacity(uint32_t new_size);
  void add(uint32_t cell, uint32_t comp);
  void addEdge(uint32_t comp1, uint32_t comp2, uint32_t version);
  bool isConnected(uint32_t comp1, uint32_t comp2, uint32_t version);
  uint32_t update(uint32_t* ccindex, uint32_t indexsize, uint32_t componentCount);

};

#endif
