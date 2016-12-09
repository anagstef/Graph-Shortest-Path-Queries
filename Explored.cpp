#include "Explored.h"

using namespace std;

Explored::Explored(){
    size = EXPLORED_INIT_SIZE;
    turn = 1;
    Index = (uint32_t*) malloc(sizeof(uint32_t)*size);
    for(uint32_t i=0;i<size;i++){
      Index[i] = 0;
    }
}

Explored::~Explored(){
    free(Index);
}

void Explored::add(uint32_t value){
   uint32_t new_size;

  if (value >= size) {
      new_size = size << 1; //double the size
      if (value >= new_size) {
          new_size = value + 1; //or make it even bigger
      }

      //realloc the index
      Index = (uint32_t*) realloc(Index, sizeof(uint32_t) * new_size);

      for (uint32_t i = size; i < new_size; i++) {
          Index[i] = 0;
      }
      size = new_size; //update index size
  }

  Index[value] = turn;

  return;

}

bool Explored::find(uint32_t value){
    if(value >= size)
      return false;

    if(Index[value] == turn)
      return true;
    else
      return false;

}

void Explored::clear(){
  turn++;
}
