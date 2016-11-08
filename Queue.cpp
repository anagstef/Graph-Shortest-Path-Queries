#include "Queue.h"
#include <fstream>
#include <sstream>

using namespace std;

Queue::Queue() {
    capacity = QUEUE_INIT_SIZE;
    queue = (uint32_t*) malloc(sizeof(uint32_t) * capacity);
    front = 0;
    end = 0;
    size = 0;
}

Queue::~Queue() {
    free(queue);
}

bool Queue::isEmpty() {
    if (size == 0) {
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
    end = capacity;
    free(queue);
    capacity = new_capacity;
    queue = new_queue;
}

uint32_t Queue::pop() {
    uint32_t ret_val;
    ret_val = queue[front];
    front = (front+1)%capacity;
    size--;
    return ret_val;
}

void Queue::clear() {
    capacity = QUEUE_INIT_SIZE;
    front = 0;
    end = 0;
    size = 0;
    queue = (uint32_t*) realloc(queue, sizeof(uint32_t) * capacity);
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
    ifstream input;
    input.open("smallGraph.txt");
    string line;
    if (input.is_open()) {
        do {
            getline(input, line);
            if (line != "S") {
                uint32_t node, neighbour;
                istringstream command(line);
                command >> node;
                command >> neighbour;
                q.push(node);
            }
        } while (line != "S");
        input.close();
    }
    q.clear();
    input.open("smallGraph.txt");
    if (input.is_open()) {
        do {
            getline(input, line);
            if (line != "S") {
                uint32_t node, neighbour;
                istringstream command(line);
                command >> node;
                command >> neighbour;
                q.push(neighbour);
            }
        } while (line != "S");
        input.close();
    }
	return 0;
}*/
