#ifndef UPDATEINDEX_H
#define UPDATEINDEX_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include "Graph.h"
#include "Templates.h"

#define CELL_SIZE 100
#define HT_UI_HASH_SIZE 1000003
// #define HT_UI_HASH_SIZE 10007
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
  int operator%(const int& a){
    return (from + to)%a;
  }
  //WARNING: EQUALITY LHS AND RHS MATTERS
  bool operator==(const UpdateIndexEdge& a){
    return (((a.from == from && a.to == to) || (a.from == to && a.to == from)) && a.version >= version);
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

  // void printHTsize(){quickFind.printSize();}

};

#endif
