#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cstdlib>
#include <cstdint>

using namespace std;

//---------------QUEUE---------------//

template <class T>
class Queue {
private:
    int front;
    int end;
    int capacity;
    uint32_t size;
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

//---------------END OF QUEUE---------------//





//---------------QUEUE---------------//

template <class T>
Queue<T>::Queue(int init_size) {
    capacity = init_size; //init capacity
    size = 0;
    front = 0;
    end = 0;
    queue = (T*) malloc(capacity * sizeof(T));
}

template <class T>
Queue<T>::~Queue() {
    free(queue);
}

template <class T>
void Queue<T>::clear() {
    size = 0;
    front = 0;
    end = 0;
}

template <class T>
bool Queue<T>::isFull() {
    if (end == capacity) return true;
    return false;
}

template <class T>
bool Queue<T>::isEmpty() {
    if (size == 0) return true;
    return false;
}

template <class T>
void Queue<T>::push(T value) {
    if (isFull()) {
        capacity = capacity*2;
        queue = (T*) realloc(queue, capacity*sizeof(T));
        queue[end] = value;
        end++;
        size++;
        return;
    }
    queue[end] = value;
    end++;
    size++;
    return;
}

template <class T>
T Queue<T>::pop() {
    T ret_value = queue[front];
    front++;
    size--;
    return ret_value;
}
//---------------END OF QUEUE---------------//

#endif
