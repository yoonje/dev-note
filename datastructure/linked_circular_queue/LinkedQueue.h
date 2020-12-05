#ifndef DATASTRUCTURE_LINKEDQUEUE_H
#define DATASTRUCTURE_LINKEDQUEUE_H

#include <cstdio>
#include "Node.h"

class LinkedQueue {
private:
    Node *front;
    Node *rear;
public:
    LinkedQueue() : front(NULL), rear(NULL) {}

    ~LinkedQueue() { while (!isEmpty()) delete deque(); }

    bool isEmpty() { return front == NULL; }

    void enqueue(Node *p);

    void enqueue(int e);

    Node *deque();

    Node *peek() { return front; }

    void display();

};


#endif //DATASTRUCTURE_LINKEDQUEUE_H
