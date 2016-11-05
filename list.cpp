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

void list::push(node &n) {
    if (head == NULL) {
        head = &n;
        head->set_next(NULL);
    }
    else {
        n.set_next(head);
        head = &n;
    }
    size++;
}

uint32_t list::pop() {
    node* temp = head;
    uint32_t ret_value;
    if (temp->get_next() != NULL) {
        ret_value = temp->get_id();
        head = temp->get_next();
        delete temp;
        size--;
        return ret_value;
    }
    else {
        ret_value = temp->get_id();
        head = NULL;
        delete temp;
        size--;
        return ret_value;
    }
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

bool list::is_empty() {
    if (size > 0) {
        return false;
    }
    return true;
}
