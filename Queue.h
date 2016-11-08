#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cstdint>
#define QUEUE_INIT_SIZE 2

class Queue {
private:
    uint32_t capacity;
    uint32_t* queue;
    uint32_t front;
    uint32_t end;
    uint32_t size;
public:
    Queue();
    ~Queue();
    uint32_t pop();
    void push(uint32_t value);
    bool isFull();
    bool isEmpty();
    void increaseCapacity();
    void clear();
    void printQueue();
    uint32_t* getQueue() { return queue; }
    uint32_t  getCap() { return capacity; }
    uint32_t  getFront() { return front; }
    uint32_t  getEnd() { return end; }
    uint32_t  getSize() { return size; }
};

#endif
