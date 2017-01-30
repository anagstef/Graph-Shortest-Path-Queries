#ifndef UPDATEINDEX_H
#define UPDATEINDEX_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
//#include "HT_Template.h"
#include "Graph.h"
#include "Templates.h"

#define CELL_SIZE 100
#define HT_UI_HASH_SIZE 500009
#define HT_UI_BUCKET_SIZE 20

struct UIndexCell{
  uint32_t* components;
  uint32_t size;
  uint32_t actual_size;
};

struct InsEdge;

class UpdateIndex{
private:
  HashTable<InsEdge> quickFind{HT_UI_HASH_SIZE, HT_UI_BUCKET_SIZE};
  UIndexCell* uindex;
  uint32_t size;
public:
  UpdateIndex(uint32_t starting_size);
  ~UpdateIndex();

  void clear();
  void increaseCapacity(uint32_t new_size);
  void add(uint32_t cell, uint32_t comp);
  void addEdge(uint32_t comp1, uint32_t comp2);
  bool isConnected(uint32_t comp1, uint32_t comp2);
  uint32_t update(uint32_t* ccindex, uint32_t indexsize, uint32_t componentCount);

};

#endif
