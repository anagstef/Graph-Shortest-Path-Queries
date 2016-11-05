#ifndef LIST_H
#define LIST_H

#include <cstdint>
#include <iostream>

class node {
private:
    uint32_t id;
    node* next;
public:
    node(int id);
    ~node();
    uint32_t get_id() { return id; }
    void set_id(int i) { id = i; }
    node* get_next() { return  next; }
    void set_next(node* n) { next = n; }
};

class list {
private:
    uint32_t size;
    node* head;
public:
    list();
    ~list();
    uint32_t get_size() { return size; }
    void set_size(uint32_t s) { size = s; }
    node* get_head() { return head; }
    void set_head(node* h) { head = h; }
    void print_list();
    void push(node* n);
    node* pop(int id);
    bool search(int id);
};

#endif
