#include "UpdateIndex.h"

using namespace std;

UpdateIndex::UpdateIndex(uint32_t starting_size){
  size = starting_size + 5;

  uindex = (UIndexCell*) malloc(sizeof(UIndexCell) * size);

  for(uint32_t i=1; i<size; i++){
    uindex[i].size = 0;
    uindex[i].actual_size = CELL_SIZE;
    uindex[i].components = (uint32_t*) malloc(sizeof(uint32_t) * CELL_SIZE);
  }

}

UpdateIndex::~UpdateIndex(){
  for(uint32_t i=1; i<size; i++){
    free(uindex[i].components);
  }
  free(uindex);
}

void UpdateIndex::increaseCapacity(uint32_t comp){
  uint32_t oldsize = size;
  size *= 2;
  if(size <= comp)
    size = comp + 5;

  uindex = (UIndexCell*) realloc(uindex, sizeof(UIndexCell) * size);

  for(uint32_t i=oldsize; i<size; i++){
    uindex[i].size = 0;
    uindex[i].actual_size = CELL_SIZE;
    uindex[i].components = (uint32_t*) malloc(sizeof(uint32_t) * CELL_SIZE);
  }

}

void UpdateIndex::add(uint32_t cell, uint32_t comp){
  if(uindex[cell].size == uindex[cell].actual_size){
    uindex[cell].actual_size *= 2;
    uindex[cell].components = (uint32_t*) realloc(uindex[cell].components, sizeof(uint32_t) * uindex[cell].actual_size);
  }

  uindex[cell].components[uindex[cell].size] = comp;
  uindex[cell].size++;
}

void UpdateIndex::clear(){
  quickFind.clear();
  for(uint32_t i = 1; i<size; i++)
    uindex[i].size = 0;
}
