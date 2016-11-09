#include "Queue.h"
#include <fstream>
#include <sstream>

using namespace std;

Queue::Queue() {
    capacity = QUEUE_INIT_SIZE; //init capacity
    queue = (uint32_t*) malloc(sizeof(uint32_t) * capacity); //malloc the array
    front = 0; //set front to 0
    end = 0;   //set end to 0
    size = 0;  //queue is empty
}

Queue::~Queue() {
    free(queue); //delete the array
}

bool Queue::isEmpty() { //return the queue status
    if (size == 0) {
        return true;
    }
    return false;
}

bool Queue::isFull() { //return the queue status
    if ((size+1) == capacity) {
        return true;
    }
    return false;
}

void Queue::push(uint32_t value) {
    if (isFull()) { //if queue is full
        increaseCapacity(); //realloc the array
    }
    queue[end] = value; //append new element at the end of the queue
    end = (end+1)%capacity; //set ending node
    size++; //increase the size
}

void Queue::increaseCapacity() {
    //printQueue();
    uint32_t new_capacity = capacity*2; //double the capacity
    queue = (uint32_t*) realloc(queue, sizeof(uint32_t) * new_capacity); //realloc a new array
    uint32_t j = front + size - end;
    for (uint32_t i = 0; i < end; ++i) { //move the values from 0 to end
        queue[j] = queue[i]; //next to the last value of the old array, now realloced
        j++;
    }
    capacity = new_capacity; //set the new capacity
    end = front + size; //end is now front + how many nodes we have

    /*uint32_t* new_queue = (uint32_t*) malloc(sizeof(uint32_t) * new_capacity);
    uint32_t j = 0;
    if (front == 0) {
        for (uint32_t i = front; i < capacity-1; ++i) {
            new_queue[j] = queue[i];
            j++;
        }
    }
    else {
        for (uint32_t i = front; i < capacity-1; ++i) {
            new_queue[j] = queue[i];
            j++;
        }
        for (uint32_t i = 0; i < end; ++i) {
            new_queue[j] = queue[i];
            j++;
        }
    }
    front = 0;
    end = capacity;
    free(queue);
    capacity = new_capacity;
    queue = new_queue;*/
}

uint32_t Queue::pop() {
    uint32_t ret_val;
    ret_val = queue[front];
    front = front+1;
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
        cout << "1 " << front << " " << end << " " << capacity << " " << size << endl;
        for (uint32_t i = front; i < end; ++i) {
            printf("%d, ", queue[i]);
        }
    }
    else if (front < end) {
        cout << "2 " << front << " " << end << " " << capacity << " " << size << endl;
        for (uint32_t i = front ; i < end; ++i) {
            printf("%d, ", queue[i]);
        }
    }
    else if (front > end) {
        cout << "3 " << front << " " << end << " " << capacity << " " << size << endl;
        for (uint32_t i = front; i < capacity; ++i) {
            printf("%d, ", queue[i]);
        }
        for (uint32_t i = 0; i < end; ++i) {
            printf("%d, ", queue[i]);
        }
    }
    cout << endl;
    cout << "------------------------------------" << endl;
}

/*int main(void) {
	Queue q;
    ifstream input;
    input.open("tinyGraph.txt");
    string line;
    if (input.is_open()) {
        do {
            getline(input, line);
            if (line != "S") {
                uint32_t node;
                istringstream command(line);
                command >> node;
                q.push(node);
            }
        } while (line != "S");
        input.close();
    }
    q.printQueue();
    q.pop();
    q.pop();
    q.pop();
    q.printQueue();
    input.open("tinyGraph.txt");
    if (input.is_open()) {
        do {
            getline(input, line);
            if (line != "S") {
                uint32_t node, neighbour;
                istringstream command(line);
                command >> node;
                cout << "neighbour " << neighbour << endl;
                command >> neighbour;
                q.push(neighbour);
            }
        } while (line != "S");
        input.close();
    }
    q.printQueue();
    return 0;
}*/
