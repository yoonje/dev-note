#include "Node.h"
#include <cstdio>

void Node::insertNext(Node *n) {
    if (n != NULL) {
        n->prev = this;
        n->next = next;
        if (next != NULL) {
            next->prev = n;
        }
        next = n;
    }
}

Node *Node::remove() {
    if (prev != NULL) prev->next = next;
    if (next != NULL) next->prev = prev;
    return this;
}