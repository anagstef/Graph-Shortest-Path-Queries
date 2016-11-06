#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cstdint>
#define QUEUE_INIT_SIZE 10

class Queue {
private:
    uint32_t capacity;
    uint32_t* queue;    
    uint32_t front;
    int end;
    uint32_t size;
    //uint32_t offset;
public:
    Queue();
    ~Queue();
    void push(uint32_t value);
    uint32_t pop();
    bool isFull();
    bool isEmpty();
    void increaseCapacity();
    uint32_t getCap() { return capacity; }
    uint32_t* getQueue() { return queue; }
};

#endif
