#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include "Node.h"
#include <cstdio>

class LinkedList {
private:
    Node org;
public:
    LinkedList() : org(0) {}

    ~LinkedList() { clear(); }

    void clear() { while (!isEmpty()) delete remove(0); }

    Node *getHead() { return org.getLink(); }

    bool isEmpty() { return getHead() == NULL; }

    Node *getEntry(int pos);

    void insert(int pos, Node *n);

    void insert(int pos, int n);

    Node* find(int val);

    Node* remove(int pos);

    void replace(int pos, Node *n);

    int size();

    void display();

};

#endif