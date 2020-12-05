#ifndef NODE_H
#define NODE_H
#include <cstdio>

class Node {
private:
    Node *prev;
    Node *next;
    int data;
public:
    Node(int val = 0) : data(val), prev(NULL), next(NULL) {}

    Node *getPrev() { return prev; }

    Node *getNext() { return next; }

    void setPrev(Node *p) { prev = p; }

    void setNext(Node *n) { next = n; }

    void display() { printf("%2d ", data); }

    bool hasData(int val) { return data == val; }

    void insertNext(Node *n);

    Node *remove();
};
#endif