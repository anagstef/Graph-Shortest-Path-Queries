#include "Queue.h"

using namespace std;

Queue::Queue() {
    capacity = QUEUE_INIT_SIZE;
    queue = (uint32_t*) malloc(sizeof(uint32_t) * capacity);
    front = 0;
    end = -1;
    size = 0;
    //offset = 0;
}

Queue::~Queue() {
    free(queue);
}

void Queue::push(uint32_t value) {
    cout << "push value " << value << endl;
    if (isFull()) {
        increaseCapacity();
    }
    end++;
    if ((uint32_t)end >= capacity && size != capacity) {
        end = 0;
    }
    queue[end] = value;
    size++;
}

uint32_t Queue::pop() {
    //na tsekaroume print tin kalesoume an queue.isEmpty
    front++;
    if (front > capacity-1) {
        uint32_t ret_val = queue[front-1];
        front = 0;
        size--;
        return ret_val;
    }
    else {
        uint32_t ret_val = queue[front-1];
        size--;
        return ret_val;
    }
}

bool Queue::isFull() {
    if (size == capacity) {
        return true;
    }
    return false;
}

bool Queue::isEmpty() {
    if (size == 0) {
        return true;
    }
    return false;
}

void Queue::increaseCapacity() {
    uint32_t newCap = capacity*2;
    uint32_t* newQueue = (uint32_t*) malloc(sizeof(uint32_t) * newCap);
    uint32_t tempFront = front;
    int index = -1;
    while (true) {
        newQueue[++index] = queue[tempFront];
        tempFront++;
        if (tempFront == capacity) {
            tempFront = 0;
        }
        if (size == (uint32_t)index+1) {
            break;
        }
    }
    queue = newQueue;
    front = 0;
    end = index;
    capacity = newCap;
}

/*int main(void) {
    Queue q;
    q.push(4);
    q.push(5);
    q.push(6);
    q.push(7);
    uint32_t* temp = q.getQueue();
    for (uint32_t i = 0; i < q.getCap(); ++i) {
        cout << temp[i] << endl;
    }
}*/
