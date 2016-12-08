#include "list.h"

using namespace std;

node::node(uint32_t i) {
    id = i;
    next = NULL;
}

node::~node() {
    delete next;
}

list::list() {
    size = 0;
    head = NULL;
    tail = NULL;
}

list::~list() {
    node* temp;
    node* the_next;
    temp = head;
    while (temp != NULL) {
        the_next = temp->get_next();
        delete temp;
        temp = the_next;
    }
    delete  temp;
}

void list::print_list() {
    node* temp = head;
    while (temp != NULL) {
        cout << temp->get_id() << endl;
        temp = temp->get_next();
    }
}

void list::push(uint32_t value) {
    node* new_node = new node(value);
    if (head == NULL) {
        head = new_node;
        tail = new_node;
        tail->set_next(tail);
    }
    else {
        tail->set_next(new_node);
    }
    size++;
}

uint32_t list::pop() {
    uint32_t ret_value;
    ret_value = head->get_id();
    head = head->get_next();
    delete(head);
    size--;
    return ret_value;
}

bool list::search(uint32_t id) {
    node* temp = head;
    while (temp != NULL) {
        if (temp->get_id() == id) {
            return true;
        }
        temp = temp->get_next();
    }
    return false;
}

bool list::isEmpty() {
    if (size > 0) return false;
    return true;
}

bool list::isFull() {
    if (size == 0) return true;
    return false;
}

int list::getSize() {
    return size;
}
