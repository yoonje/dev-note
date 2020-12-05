#include "LinkedList.h"
#include <cstdio>

Node *LinkedList::getEntry(int pos) {
    Node *n = &org;
    for (int i = -1; i < pos; i++, n = n->getLink())
        if (n == NULL)
            break;
    return n;
}

void LinkedList::insert(int pos, Node *n) {
    Node *prev = getEntry(pos - 1);
    if (prev != NULL)
        prev->insertNext(n);
}

void LinkedList::insert(int pos, int n) {
    Node* temp_node = new Node(n);
    Node *prev = getEntry(pos - 1);
    if (prev != NULL)
        prev->insertNext(temp_node);
}

Node *LinkedList::remove(int pos) {
    Node *prev = getEntry(pos - 1);
    return prev->removeNext();
}

Node *LinkedList::find(int val) {
    for (Node *p = getHead(); p != NULL; p = p->getLink()) {
        if (p->hasData(val)) {
            return p;
        }
    }
    return NULL;
}

void LinkedList::replace(int pos, Node *n) {
    Node *prev = getEntry(pos - 1);
    if (prev != NULL) {
        delete prev->removeNext();
        prev->insertNext(n);
    }
}

int LinkedList::size() {
    int count = 0;
    for (Node *p = getHead(); p != NULL; p = p->getLink())
        count++;
    return count;
}

void LinkedList::display() {
    printf("total items %2d: ", size());
    for (Node *p = getHead(); p != NULL; p = p->getLink())
        p->display();
    printf("\n");
}