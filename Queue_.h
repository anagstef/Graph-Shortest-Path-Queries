#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cstdint>
#define QUEUE_INIT_SIZE 10

struct line_col {
    int line;
    int column;
};

template <class T>
class Queue {
private:
    int datasize;
    int capacity;
    int currsize;
    int data;
    line_col front;
    line_col end;
    T** queue;
public:
    Queue(int data);
    ~Queue();
    T pop();
    void push(T value);
    bool isFull();   //is size == capacity?
    bool isEmpty();  //is size == 0?
    void increaseCapacity();
    void clear(); //reset the queue
    void printQueue(); //unit testing
    //setters - getters
    T** getQueue() { return queue; }
    int  getCap() { return capacity; }
    int  getFront() { return front; }
    int  getEnd() { return end; }
    int  getSize() { return currsize; }
};

#endif
