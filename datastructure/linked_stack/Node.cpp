#include "Node.h"
#include <cstdio>
Node *Node::removeNext() {
    Node *removed = link;
    if (removed != NULL)
        link = removed->link;
    return removed;
}

void Node::insertNext(Node *n) {
    if (n != NULL) {
        n->link = link;
        link = n;
    }
}

void Node::display() {
    printf("%2d ", data);
}