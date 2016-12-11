#ifndef STACK_H
#define STACK_H

#include <cstdint>
#define STACK_INIT_SIZE 100

template <class T>
class Stack {
private:
    int end;
    int capacity;
    int size;
    T* stack;
public:
    Stack();
    ~Stack();
    T pop();
    void push(T value);
    bool isFull();
    bool isEmpty();
    void increaseCapacity();
    void clear();
    //setters - getters
    T* getStack() { return stack; }
    int  getCap() { return capacity; }
    int  getEnd() { return end; }
    int  getSize() { return size; }
};

#include "Stack.cpp"
#endif
