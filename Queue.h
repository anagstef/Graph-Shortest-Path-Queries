#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cstdint>
#define QUEUE_INIT_SIZE 15

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
    void push(uint32_t value);
    uint32_t pop();
    bool isFull();
    bool isEmpty();
    void increaseCapacity();
    uint32_t* getQueue() { return queue; }
    uint32_t  getCap() { return capacity; }
    uint32_t  getFront() { return front; }
    uint32_t  getEnd() { return end; }
    void printQueue();
};

#endif
