#ifndef LIST_H
#define LIST_H

#include <cstdint>
#include <iostream>

class node {
private:
    uint32_t id;
    node* next;
public:
    node(uint32_t i);
    ~node();
    uint32_t get_id() { return id; }
    void set_id(int i) { id = i; }
    node* get_next() { return  next; }
    void set_next(node* n) { next = n; }
};

class list {
private:
    int size;
    node* head;
public:
    list();
    ~list();
    void print_list();
    void push(node& n);
    uint32_t pop();
    bool search(uint32_t id);
    bool is_empty();
};

#endif
