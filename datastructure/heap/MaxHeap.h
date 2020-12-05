#ifndef DATASTRUCTURE_MAXHEAP_H
#define DATASTRUCTURE_MAXHEAP_H

#include "HeapNode.h"

#define MAX_ELEMENT 200

class MaxHeap {
private:
    HeapNode node[MAX_ELEMENT];
    int size;
public:
    MaxHeap() : size(0) {}

    bool isEmpty() { return size == 0; }

    bool isFull() { return size == MAX_ELEMENT - 1; }

    HeapNode &getParent(int i) { return node[i / 2]; }

    HeapNode &getLeft(int i) { return node[i * 2]; }

    HeapNode &getRight(int i) { return node[i * 2 + 1]; }

    void insert(int key);

    HeapNode remove();

    HeapNode find() { return node[1]; }

    void display() {
        for (int i = 1, level = 1; i < size; i++) {
            if (i == level) {
                printf("\n");
                level *= 2;
            }
            node[i].display();
        }
        printf("\n----------------------------------");
    }

};


#endif //DATASTRUCTURE_MAXHEAP_H
