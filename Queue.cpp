#include "Queue.h"

using namespace std;

Queue::Queue() {
    capacity = QUEUE_INIT_SIZE; //init capacity
    size = 0;
    front = 0;
    end = 0;
    queue = (uint32_t*) malloc(capacity * sizeof(uint32_t));
    //printf("Queue is ready\n");
}

Queue::~Queue() {
    free(queue);
}

void Queue::clear() {
    size = 0;
    front = 0;
    end = 0;
}

bool Queue::isFull() {
    if (end == capacity) return true;
    return false;
}

bool Queue::isEmpty() {
    if (size == 0) return true;
    return false;
}

void Queue::push(uint32_t value) {
    if (isFull()) {
        capacity = capacity*2;
        queue = (uint32_t*) realloc(queue, capacity*sizeof(uint32_t));
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

uint32_t Queue::pop() {
    uint32_t ret_value = queue[front];
    front++;
    size--;
    return ret_value;
}
