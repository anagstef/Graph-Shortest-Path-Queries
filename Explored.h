#ifndef EXPLORED_H
#define EXPLORED_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <new>
#define EXPLORED_INIT_SIZE 1000

class Explored{
private:
  uint32_t* Index;
  uint32_t size;
  uint32_t turn;
public:
  Explored();
  ~Explored();

  void add(uint32_t value);
  bool find(uint32_t value);
  void clear();
};

#endif
