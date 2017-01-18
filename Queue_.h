#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cstdint>


template <class T>
class Queue {
private:
    int front;
    int end;
    int capacity;
    uint32_t size;
    //uint32_t* queue;

public:
    T* queue;
    Queue(int init_size);
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
    uint32_t  getSize() { return size; }
};

#include "Queue_.cpp"
#endif
