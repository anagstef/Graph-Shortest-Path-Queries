#ifndef EXPLORED_H
#define EXPLORED_H

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <new>


class Explored{
private:
  uint32_t* Index;
  uint32_t size;
  uint32_t turn;
public:
  Explored(uint32_t init_size);
  ~Explored();

  void add(uint32_t value);
  bool find(uint32_t value);
  void clear();
};

#endif
