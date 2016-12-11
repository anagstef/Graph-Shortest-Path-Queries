#ifndef UPDATEINDEX_H
#define UPDATEINDEX_H

#include <iostream>
#include "HT_Template.h"
#include "Graph.h"
#include "CC.h"

#define CELL_SIZE 10

struct UIndexCell{
  uint32_t* components;
  uint32_t size;
  uint32_t actual_size;
}

class UpdateIndex{
private:
  HashTable<InsEdge> quickFind;
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
  void update(CC& cc);

};

#endif
