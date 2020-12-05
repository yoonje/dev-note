#include "DLinkedList.h"

Node *DLinkedList::getEntry(int pos) {
    Node *n = &org;
    for (int i = -1; i < pos; i++, n = n->getNext()) {
        if (n == NULL)
            break;
    }
    return n;
}

void DLinkedList::insert(int pos, Node* n) {
    Node *prev = getEntry(pos - 1);
    if (prev != NULL)
        prev->insertNext(n);
}

void DLinkedList::insert(int pos, int n) {
    Node *prev = getEntry(pos - 1);
    if (prev != NULL) {
        prev->insertNext(new Node(n));
    }
}

Node *DLinkedList::remove(int pos) {
    Node *n = getEntry(pos);
    return n->remove();
}

Node *DLinkedList::find(int val) {
    for (Node *p = getHead(); p != NULL; p = p->getNext()) {
        if (p->hasData(val))
            return p;
    }
    return NULL;
}

void DLinkedList::replace(int pos, Node *n) {
    Node *prev = getEntry(pos - 1);
    if (prev != NULL) {
        delete prev->getNext()->remove();
        prev->insertNext(n);
    }
}

int DLinkedList::size() {
    int count = 0;
    for (Node *p = getHead(); p != NULL; p = p->getNext())
        count++;
    return count;
}

void DLinkedList::display() {
    printf("이중 연결 리스트 항목의 수 = %2d ", size());
    for (Node *p = getHead(); p != NULL; p = p->getNext())
        p->display();
    printf("\n");
}