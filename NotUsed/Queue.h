#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cstdint>
#define QUEUE_INIT_SIZE 100

//cyclic array for queue implementation

class Queue {
private:
    int capacity; //how many uint32_t can fit in the table
    uint32_t* queue;   //the table
    int front;    //1st element of the table
    int end;      //last element of the table
    int size;     //offset
public:
    Queue();
    ~Queue();
    uint32_t pop();  //append the head of the queue
    void push(uint32_t value); //add an element in the queue
    bool isFull();   //is size == capacity?
    bool isEmpty();  //is size == 0?
    void increaseCapacity();  //realloc the queue
    void clear(); //reset the queue
    void printQueue(); //unit testing
    //setters - getters
    uint32_t* getQueue() { return queue; }
    int  getCap() { return capacity; }
    int  getFront() { return front; }
    int  getEnd() { return end; }
    int  getSize() { return size; }
};

#endif
