#ifndef DATASTRUCTURE_DLINKEDLIST_H
#define DATASTRUCTURE_DLINKEDLIST_H

#include "Node.h"

class DLinkedList {
private:
    Node org;
public:
    DLinkedList() : org(0) {}

    void clear() { while (!isEmpty()) delete remove(0); }

    ~DLinkedList() { while (!isEmpty()) delete remove(0); }

    Node *getHead() { return org.getNext(); }

    bool isEmpty() { return getHead() == NULL; }

    Node *getEntry(int pos);

    void insert(int pos, Node* n);

    void insert(int pos, int n);

    Node *remove(int pos);

    Node *find(int val);

    void replace(int pos, Node *n);

    int size();

    void display();

};


#endif
