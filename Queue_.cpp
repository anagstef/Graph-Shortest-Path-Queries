#include "Queue_.h"
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

template <class T>
Queue<T>::Queue(int d) {
    capacity = QUEUE_INIT_SIZE; //init capacity
    currsize = 0;
    data = d;
    front.line = 0;
    end.line = -1;
    front.column = 0;
    end.column = -1;
    int arrays;
    arrays = data/capacity;
    if (arrays != 0) arrays++;
    queue = (T**) malloc(arrays * sizeof(T*));
    queue[0] = (T*) malloc(capacity * sizeof(T));
}

template <class T>
Queue<T>::~Queue() {

}

template <class T>
bool Queue<T>::isFull() {
    if (currsize == datasize) return true;
    return false;
}

template <class T>
bool Queue<T>::isEmpty() {
    if (currsize == 0) return true;
    return false;
}

template <class T>
T Queue<T>::pop() {
    T value = queue[front.line][front.column];
    front.column++;
    if (front.column == capacity) {
        free(queue[front.line]);
        front.line = front.line + 1;
        front.column = 0;
    }
    currsize--;
    return value;
}

template <class T>
void Queue<T>::push(T value) {
    printf("Inserting --%u\n", value);
    if (end.line == -1) {
        queue[0][0] = value;
        end.column = 1;
        end.line = 0;
        currsize++;
        return;
    }
    else if (end.column == capacity) {
        printf("New array for %u line: %d column: %d\n", value, end.line, end.column);
        queue[end.line + 1] = (T*) malloc(capacity * sizeof(T));
        end.line = end.line + 1;
        end.column = 0;
        queue[end.line][0] = value;
        end.column = end.column + 1;
        currsize++;
        return;
    }
    else {
        queue[end.line][end.column] = value;
        end.column = end.column + 1;
        currsize++;
        return;
    }
}

template <class T>
void Queue<T>::clear() {

}

template <class T>
void Queue<T>::printQueue() {
    int i, j;
    printf("FL %d FC %d EL %d EC %d\n", front.line, front.column, end.line, end.column);
    for (i = front.line; i <= end.line; ++i) {
        if (i == front.line) {
            for (j = front.column; j < capacity; ++j) {
                //printf("-i %d- -j %d-", i,j);
                printf("%d, ", queue[i][j]);
            }
        }
        else {
            for (j = 0; j < capacity; ++j) {
                //printf("-i %d- -j %d-", i,j);
                printf("%d, ", queue[i][j]);
            }
        }
    }
    cout << endl;
}

/*int main(void) {
	Queue<uint32_t> q(500);
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
}*/
