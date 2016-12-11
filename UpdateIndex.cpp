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

void UpdateIndex::increaseCapacity(uint32_t new_size){
  uindex = (UIndexCell*) realloc(uindex, sizeof(UIndexCell) * new_size);

  for(uint32_t i=size; i<new_size; i++){
    uindex[i].size = 0;
    uindex[i].actual_size = CELL_SIZE;
    uindex[i].components = (uint32_t*) malloc(sizeof(uint32_t) * CELL_SIZE);
  }

  size = new_size;

}

void UpdateIndex::addEdge(uint32_t comp1, uint32_t comp2){
  InsEdge edge;
  if(comp1 >= size || comp2 >= size){
    uint32_t new_size = size * 2;
    if(comp1 >= new_size || comp2 >= new_size){
      new_size = comp1 + 5;
      if(comp2 >= new_size)
        new_size = comp2 + 5;
    }
    increaseCapacity(new_size);
  }

  //get the set of components of the comp1
  uint32_t size1 = uindex[comp1].size + 1;
  uint32_t* comp1_neighbors = (uint32_t*) malloc(sizeof(uint32_t) * size1);

  comp1_neighbors[0] = comp1;
  for(uint32_t i=0; i<uindex[comp1].size; i++)
    comp1_neighbors[i+1] = uindex[comp1].components[i];

  //get the set of components of the comp2
  uint32_t size2 = uindex[comp2].size + 1;
  uint32_t* comp2_neighbors = (uint32_t*) malloc(sizeof(uint32_t) * size2);

  comp2_neighbors[0] = comp2;
  for(uint32_t i=0; i<uindex[comp2].size; i++)
    comp2_neighbors[i+1] = uindex[comp2].components[i];

  //add comp1 set to every node in the comp2 set
  for(uint32_t i=0; i<size2; i++){
    for(uint32_t j=0; j<size1; j++){
      add(comp2_neighbors[i], comp1_neighbors[j]);
      edge.from = comp2_neighbors[i];
      edge.to = comp1_neighbors[j];
      quickFind.add(edge);
    }
  }

  //add comp2 set to every node in the comp1 set
  for(uint32_t i=0; i<size1; i++){
    for(uint32_t j=0; j<size2; j++){
      add(comp1_neighbors[i], comp2_neighbors[j]);
      edge.from = comp1_neighbors[i];
      edge.to = comp2_neighbors[j];
      quickFind.add(edge);
    }
  }

  free(comp1_neighbors);
  free(comp2_neighbors);
}

void UpdateIndex::add(uint32_t cell, uint32_t comp){
  if(uindex[cell].size == uindex[cell].actual_size){
    uindex[cell].actual_size *= 2;
    uindex[cell].components = (uint32_t*) realloc(uindex[cell].components, sizeof(uint32_t) * uindex[cell].actual_size);
  }

  uindex[cell].components[uindex[cell].size] = comp;
  uindex[cell].size++;
}

bool isConnected(uint32_t comp1, uint32_t comp2){
  InsEdge edge;
  edge.from = comp1;
  edge.to = comp2;
  return quickFind.find(edge);
}

void update(CC& CC){
  uint32_t currCC = 1;

  bool* visited = (bool*) malloc(sizeof(bool) * CC->componentCount);
  for(uint32_t i=1; i< CC->componentCount; i++){
    visited[i] = false;
  }

  for(uint32_t i=1; (i<size) && (i< CC->componentCount); i++){ //for every CC in update index
    if(!visited[i]){ //if it is not visited yet
      for(uint32_t j=0; j< CC->indexsize; j++){ //run through the whole ccindex
        if(CC->ccindex[j] >= i){ //if the CC is greater than the current CC of the update
          if(CC->ccindex[j] == i)
            CC->ccindex[j] = currCC;
          else{
            for(uint32_t k=0; k < uindex[i].size ; k++){
              if(CC->ccindex[j] == uindex[i].components[k]){
                CC->ccindex[j] = currCC;
                break;
              }
            }
          }
        }
      }
      visited[i] = true;
      for(uint32_t k=0; k < uindex[i].size ; k++)
        visited[uindex[i].components[k]] = true;

      currCC++;
    }
  }

  CC->componentCount = currCC;
  clear();
}

void UpdateIndex::clear(){
  quickFind.clear();
  for(uint32_t i = 1; i<size; i++)
    uindex[i].size = 0;
}
