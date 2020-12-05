#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include <cstdio>
#include "Node.h"

class LinkedStack {
private:
    Node *top;
public:
    LinkedStack() { top = NULL; }

    ~LinkedStack() { while (!isEmpty()) delete pop(); }

    bool isEmpty() { return top == NULL; }

    void push(Node* p);

    void push(int e);

    Node *pop();

    Node *peek();

    void display();
};

#endif
