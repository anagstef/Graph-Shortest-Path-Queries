#include "Queue.h"
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

Queue::Queue() {
    capacity = QUEUE_INIT_SIZE; //init capacity
    queue = (uint32_t*) malloc(sizeof(uint32_t) * capacity); //malloc the array
    front = 0;
    end = -1;
    size = 0;
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
    if (size == capacity - 1) {
        return true;
    }
    return false;
}

void Queue::push(uint32_t value) {
    if (isFull()) {
        //cout << "INCREASING CAPACITY AT " << value << endl;
        increaseCapacity();
    }
    end++;
    if (end > capacity && size != capacity) {
        end = 0;
    }
    queue[end] = value;
    size++;
}

void Queue::increaseCapacity() {
    int new_capacity = capacity*2;
    queue = (uint32_t*) realloc(queue, sizeof(uint32_t) * new_capacity);
    //int temp_end = size + 1;
    //if (queue[0] != queue[front]) {
        //for (int i = 0; i <= end; ++i) {
        //  queue[temp_end] = queue[i];
        //  temp_end++;
        //}
    //}
    int temp_end = capacity;
    if (end < front) {
        for (int i = 0; i <= end; ++i) {
            temp_end++;
            queue[temp_end] = queue[i];
        }
    }
    capacity = new_capacity;
    end = front + size - 1;
}

uint32_t Queue::pop() {
    uint32_t ret_val;
    ret_val = queue[front];
    front++;
    if (front == capacity) {
        front = 0;
    }
    size--;
    return ret_val;
}

void Queue::clear() {
    capacity = QUEUE_INIT_SIZE;
    front = 0;
    end = -1;
    size = 0;
    queue = (uint32_t*) realloc(queue, sizeof(uint32_t) * capacity);
}

void Queue::printQueue() {
    if (front == 0) {
        //cout << "1 " << front << " " << end << " " << capacity << " " << size << endl;
        for (int i = front; i <= end; ++i) {
            printf("%d, ", queue[i]);

        }
    }
    else if (front < end) {
        //cout << "2 " << front << " " << end << " " << capacity << " " << size << endl;
        for (int i = front ; i <= end; ++i) {
            printf("%d, ", queue[i]);
        }
    }
    else if (front > end) {
        //cout << "3 " << front << " " << end << " " << capacity << " " << size << endl;
        for (int i = front; i <= capacity; ++i) {
            printf("%d, ", queue[i]);
        }
        for (int i = 0; i <= end; ++i) {
            printf("%d, ", queue[i]);
        }
    }
    cout << endl;
    cout << "-------------------------------------------------------------------" << endl;
}

/*int main(void) {
	Queue q;
    queue<uint32_t> q1;
    queue<uint32_t> temp1;
    ifstream input;
    input.open("tinyGraph.txt");
    string line;
    int i = 0;
    if (input.is_open()) {
        do {
            getline(input, line);
            if (line != "S") {
                uint32_t node;
                istringstream command(line);
                command >> node;
                q.push(i);
                q1.push(i);
                ++i;
            }
        } while (line != "S" && i < 25);
        input.close();
    }
    q.printQueue();
    temp1 = q1;
    cout << "STD QUEUE" << endl;
    while (!temp1.empty()) {
        uint32_t val = temp1.front();
        printf("%d, ", val);
        temp1.pop();
    }
    cout << endl;
    cout << "END OF STD QUEUE" << endl;
    q.pop();q.pop();q.pop();q.pop();q.pop();q.pop();q.pop();q.pop();q.pop();q.pop();q.pop();q.pop();q.pop();
    q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();
    q.printQueue();
    temp1 = q1;
    cout << "STD QUEUE" << endl;
    while (!temp1.empty()) {
        uint32_t val = temp1.front();
        printf("%d, ", val);
        temp1.pop();
    }
    cout << endl;
    cout << "END OF STD QUEUE" << endl;
    cout << "Add more" << endl;
    for (i = 35; i < 45; ++i) {
        q.push(i);
        q1.push(i);
    }
    q.printQueue();
    temp1 = q1;
    cout << "STD QUEUE" << endl;
    while (!temp1.empty()) {
        uint32_t val = temp1.front();
        printf("%d, ", val);
        temp1.pop();
    }
    cout << endl;
    cout << "END OF STD QUEUE" << endl;
    cout << "Pop more" << endl;
    q.pop();q.pop();q.pop();q.pop();q.pop();q.pop();q.pop();q.pop();q.pop();q.pop();q.pop();q.pop();q.pop();
    q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();q1.pop();
    q.printQueue();
    temp1 = q1;
    cout << "STD QUEUE" << endl;
    while (!temp1.empty()) {
        uint32_t val = temp1.front();
        printf("%d, ", val);
        temp1.pop();
    }
    cout << endl;
    cout << "END OF STD QUEUE" << endl;
    input.open("tinyGraph.txt");
    if (input.is_open()) {
        do {
            getline(input, line);
            if (line != "S") {
                uint32_t node, neighbour;
                istringstream command(line);
                command >> node;
                command >> neighbour;
                q.push(neighbour);
                q1.push(neighbour);
            }
        } while (line != "S");
        input.close();
    }
    for (i = 0; i < 36; ++i) {
        q.push(i);
        q1.push(i);
    }
    q.printQueue();
    temp1 = q1;
    cout << "STD QUEUE" << endl;
    while (!temp1.empty()) {
        uint32_t val = temp1.front();
        printf("%d, ", val);
        temp1.pop();
    }
    cout << endl;
    cout << "END OF STD QUEUE" << endl;
    for (i = 0; i < 20; ++i) {
        q.pop();
        q1.pop();
    }
    q.printQueue();
    temp1 = q1;
    cout << "STD QUEUE" << endl;
    while (!temp1.empty()) {
        uint32_t val = temp1.front();
        printf("%d, ", val);
        temp1.pop();
    }
    cout << endl;
    cout << "END OF STD QUEUE" << endl;
    return 0;
}*/
