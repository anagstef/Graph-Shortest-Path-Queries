#include "Queue.h"

using namespace std;

Queue::Queue() {
    capacity = QUEUE_INIT_SIZE;
    queue = (uint32_t*) malloc(sizeof(uint32_t) * capacity-1);
    front = 0;
    end = 0;
    size = 0;
}

Queue::~Queue() {
    free(queue);
}

bool Queue::isEmpty() {
    if (front == 0 && end == 0) {
        return true;
    }
    return false;
}


bool Queue::isFull() {
    if ((end+1)%capacity == front) {
        return true;
    }
    return false;
}

void Queue::push(uint32_t value) {
    if (isEmpty()) {
        queue[front] = value;
        end = (end+1)%capacity;
        size++;
        return;
    }
    if (isFull()) {
        increaseCapacity();
    }
    queue[end] = value;
    end = (end+1)%capacity;
    size++;
}

void Queue::increaseCapacity() {
    uint32_t new_capacity = capacity*2;
    uint32_t* new_queue = (uint32_t*) malloc(sizeof(uint32_t) * new_capacity);
    uint32_t j = 0;
    if (front == 0) {
        for (uint32_t i = front; i < capacity; ++i) {
            new_queue[j] = queue[i];
            j++;
        }
    }
    else {
        for (uint32_t i = front; i < capacity; ++i) {
            new_queue[j] = queue[i];
            j++;
        }
        for (uint32_t i = 0; i <= end; ++i) {
            new_queue[j] = queue[i];
            j++;
        }
    }

    front = 0;
    end = capacity-1;
    capacity = new_capacity;
    queue = new_queue;
}

uint32_t Queue::pop() {
    uint32_t ret_val;
    ret_val = queue[front];
    front = (front+1)%capacity;
    return ret_val;
}

void Queue::printQueue() {
    if (front == 0) {
        for (uint32_t i = front; i < end; ++i) {
            cout << queue[i] << endl;
        }
    }
    else if (front < end) {
        for (uint32_t i = front ; i < end; ++i) {
            cout << queue[i] << endl;
        }
    }
    else {
        for (uint32_t i = front; i < capacity; ++i) {
            cout << queue[i] << endl;
        }
        for (uint32_t i = 0; i < end; ++i) {
            cout << queue[i] << endl;
        }
    }
}

/*int main(void) {
	Queue q;
	q.push(4);
	q.push(5);
	q.push(6);
	q.push(7);
	q.push(8);
	q.push(9);
	q.printQueue();
	q.pop();
	q.push(10);
	q.push(11);
	q.push(12);
	q.push(13);
	q.push(14);
	q.push(15);
	q.push(16);
	q.push(17);
	q.push(18);
	q.push(19);
	q.push(20);
	q.printQueue();
	return 0;
}*/
