#include "Stack.h"

using namespace std;

template <class T>
Stack<T>::Stack() {
    capacity = STACK_INIT_SIZE; //init capacity
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
    if (!isEmpty()) {
        T ret_value = stack[end];
        end--;
        size--;
        return ret_value;
    }
}
