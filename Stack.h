#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <cstdlib>
#include <cstdint>

using namespace std;

//---------------STACK---------------//

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

//---------------END OF STACK---------------//

//---------------STACK---------------//

template <class T>
Stack<T>::Stack(int init_size) {
    capacity = init_size; //init capacity
    size = 0;
    end = 0;
    stack = (T*) malloc(capacity * sizeof(T));
}

template <class T>
Stack<T>::~Stack() {
    free(stack);
}

template <class T>
void Stack<T>::clear() {
    size = 0;
    end = 0;
}

template <class T>
bool Stack<T>::isFull() {
    if (end == capacity) return true;
    return false;
}

template <class T>
bool Stack<T>::isEmpty() {
    if (size == 0) return true;
    return false;
}

template <class T>
void Stack<T>::push(T value) {
    if (isFull()) {
        capacity = capacity*2;
        stack = (T*) realloc(stack, capacity*sizeof(T));
        stack[end] = value;
        end++;
        size++;
        return;
    }
    stack[end] = value;
    end++;
    size++;
    return;
}

template <class T>
T Stack<T>::pop() {
    end--;
    T ret_value = stack[end];
    size--;
    return ret_value;
}

//---------------END OF STACK---------------//

#endif
