#include <cstdio>
#include <cstdlib>
#include "LinkedStack.h"

void LinkedStack::push(int e) {
    Node* p = new Node(e);
    if (isEmpty())
        top = p;
    else {
        p->setLink(top);
        top = p;
    }
}

void LinkedStack::push(Node *p) {
    if (isEmpty())
        top = p;
    else {
        p->setLink(top);
        top = p;
    }
}

Node *LinkedStack::pop() {
    if (isEmpty())
        return NULL;
    Node*p = top;
    top = top->getLink();
    return p;
}

Node *LinkedStack::peek() {
    return top;
}

void LinkedStack::display() {
    for (Node* p = top; p != NULL; p=p->getLink()) {
        p->display();
    }
    printf("\n");
}