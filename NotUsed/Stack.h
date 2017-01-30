#ifndef STACK_H
#define STACK_H

#include <cstdint>
#include <cstdlib>

template <class T>
class Stack {
private:
    int end;
    int capacity;
    int size;
    T* stack;
public:
    Stack(int init_size);
    ~Stack();
    T pop();
    void push(T value);
    bool isFull();
    bool isEmpty();
    void increaseCapacity();
    void clear();
    //setters - getters
    T* getStack()  { return stack; }
    int  getCap()  { return capacity; }
    int  getEnd()  { return end; }
    int  getSize() { return size; }
    void setEnd(int e)  { end = e; }
    void setSize(int s) { size = s; }
    T top() { return stack[end]; }
};

#include "Stack.cpp"
#endif
