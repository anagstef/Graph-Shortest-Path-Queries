#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cstdint>
#define QUEUE_INIT_SIZE 100

template <class T>
class Queue {
private:
    int front;
    int end;
    int capacity;
    int size;
    T* queue;
public:
    Queue();
    ~Queue();
    T pop();
    void push(T value);
    bool isFull();   //is size == capacity?
    bool isEmpty();  //is size == 0?
    void increaseCapacity();
    void clear(); //reset the queue
    void printQueue(); //unit testing
    //setters - getters
    T* getQueue() { return queue; }
    int  getCap() { return capacity; }
    int  getFront() { return front; }
    int  getEnd() { return end; }
    int  getSize() { return size; }
};

#include "Queue_.cpp"
#endif
