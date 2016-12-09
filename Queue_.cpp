#include "Queue_.h"
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

template <class T>
Queue<T>::Queue() {
//Queue::Queue() {
    capacity = QUEUE_INIT_SIZE; //init capacity
    size = 0;
    front = 0;
    end = 0;
    queue = (T*) malloc(capacity * sizeof(T));
    //printf("Queue is ready\n");
}

template <class T>
Queue<T>::~Queue() {
//Queue::~Queue() {
    free(queue);
}

template <class T>
void Queue<T>::clear() {
//void Queue::clear() {
    size = 0;
    front = 0;
    end = 0;
}

template <class T>
bool Queue<T>::isFull() {
//bool Queue::isFull() {
    if (end == capacity) return true;
    return false;
}

template <class T>
bool Queue<T>::isEmpty() {
//bool Queue::isEmpty() {
    if (size == 0) return true;
    return false;
}

template <class T>
void Queue<T>::push(T value) {
//void Queue::push(uint32_t value) {
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
//uint32_t Queue::pop() {
    T ret_value = queue[front];
    front++;
    size--;
    return ret_value;
}

//template <class T>
//void Queue<T>::printQueue() {
//    for (int i = front; i < end; ++i) printf("%u, ", queue[i]);
//    cout << endl;
//}

/*int main(void) {
	Queue<uint32_t> q;
    queue<uint32_t> q1;
    queue<uint32_t> temp1;
    ifstream input;
    input.open("tinyGraph.txt");
    string line;
    int i = 1;
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
}
*/
