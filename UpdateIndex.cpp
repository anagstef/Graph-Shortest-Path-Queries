#include "UpdateIndex.h"

#define DEBUG 0

using namespace std;

UpdateIndex::UpdateIndex(uint32_t starting_size){
  size = starting_size * 2;

  uindex = (UIndexCell*) malloc(sizeof(UIndexCell) * size);

  for(uint32_t i=1; i<size; i++){
    uindex[i].size = 0;
    uindex[i].actual_size = CELL_SIZE;
    uindex[i].components = (uint32_t*) malloc(sizeof(uint32_t) * CELL_SIZE);
  }
}

UpdateIndex::~UpdateIndex(){

  //////////////////DEBUG////////////////////
  // if(DEBUG)
  //   quickFind.printSize();
  //////////////////DEBUG////////////////////

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

void UpdateIndex::addEdge(uint32_t comp1, uint32_t comp2, uint32_t version){
  // InsEdge edge;
  UpdateIndexEdge edge;
  edge.version = version;
  // cerr << "before increaseCapacity" << endl;
  if(comp1 >= size || comp2 >= size){
    uint32_t new_size = size * 2;
    if(comp1 >= new_size || comp2 >= new_size){
      new_size = comp1 * 2;
      if(comp2 >= new_size)
        new_size = comp2 * 2;
    }
    increaseCapacity(new_size);
  }
  // cerr << "after increaseCapacity" << endl;
  //get the set of components of the comp1
  uint32_t size1 = uindex[comp1].size;

  //get the set of components of the comp2
  uint32_t size2 = uindex[comp2].size;
  // cerr << "comp1" << endl;
  //add comp1 set to every node in the comp2 set
  add(comp2, comp1);
  edge.from = comp2;
  edge.to = comp1;
  quickFind.add(edge);

  for(uint32_t j=0; j<size1; j++){
    add(comp2, uindex[comp1].components[j]);
    edge.from = comp2;
    edge.to = uindex[comp1].components[j];
    quickFind.add(edge);
  }

  for(uint32_t i=0; i<size2; i++){
    add(uindex[comp2].components[i], comp1);
    edge.from = uindex[comp2].components[i];
    edge.to = comp1;
    quickFind.add(edge);
    for(uint32_t j=0; j<size1; j++){
      add(uindex[comp2].components[i], uindex[comp1].components[j]);
      edge.from = uindex[comp2].components[i];
      edge.to = uindex[comp1].components[j];
      quickFind.add(edge);
    }
  }

  //add comp2 set to every node in the comp1 set
  add(comp1, comp2);
  // edge.from = comp1;
  // edge.to = comp2;
  // quickFind.add(edge);

  for(uint32_t j=0; j<size2; j++){
    add(comp1, uindex[comp2].components[j]);
    // edge.from = comp1;
    // edge.to = uindex[comp2].components[j];
    // quickFind.add(edge);
  }

  for(uint32_t i=0; i<size1; i++){

    add(uindex[comp1].components[i], comp2);
    // edge.from = uindex[comp1].components[i];
    // edge.to = comp2;
    // quickFind.add(edge);

    for(uint32_t j=0; j<size2; j++){
      add(uindex[comp1].components[i], uindex[comp2].components[j]);
      // edge.from = uindex[comp1].components[i];
      // edge.to = uindex[comp2].components[j];
      // quickFind.add(edge);
    }

  }
}

void UpdateIndex::add(uint32_t cell, uint32_t comp){
  if(uindex[cell].size == uindex[cell].actual_size){
    // cerr << "size increased" << endl;
    uindex[cell].actual_size *= 2;
    uindex[cell].components = (uint32_t*) realloc(uindex[cell].components, sizeof(uint32_t) * uindex[cell].actual_size);
  }

  uindex[cell].components[uindex[cell].size] = comp;
  uindex[cell].size++;
}

bool UpdateIndex::isConnected(uint32_t comp1, uint32_t comp2, uint32_t version){
  UpdateIndexEdge edge;
  // InsEdge edge;
  edge.from = comp1;
  edge.to = comp2;
  edge.version = version;
  return quickFind.find(edge);
}

//DEPRECATED
uint32_t UpdateIndex::update(uint32_t* ccindex, uint32_t indexsize, uint32_t componentCount){
  uint32_t currCC = 1;

  bool* visited = (bool*) malloc(sizeof(bool) * componentCount);
  for(uint32_t i=1; i< componentCount; i++){
    visited[i] = false;
  }

  for(uint32_t i=1; (i<size) && (i<componentCount); i++){ //for every CC in update index
    // std::cout << "For comp " << i;
    if(!visited[i]){ //if it is not visited yet
      for(uint32_t j=0; j<indexsize; j++){ //run through the whole ccindex
        std::cout << "For comp " << i << " at index position " << j << endl;
        if(ccindex[j] >= i){ //if the CC is greater than the current CC of the update
          if(ccindex[j] == i)
            ccindex[j] = currCC;
          else{
            for(uint32_t k=0; k < uindex[i].size ; k++){
              // std::cout << "looping here3???" << std::endl;
              if(ccindex[j] == uindex[i].components[k]){
                ccindex[j] = currCC;
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

  clear();
  return currCC;
}

void UpdateIndex::clear(){
  quickFind.clear();
  for(uint32_t i = 1; i<size; i++)
    uindex[i].size = 0;
}
