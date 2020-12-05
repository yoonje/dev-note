#ifndef DATASTRUCTURE_HEAPNODE_H
#define DATASTRUCTURE_HEAPNODE_H

#include <cstdio>

class HeapNode {
private:
    int key;
public:
    HeapNode(int k = 0) : key(k) {}

    void setKey(int k) { key = k; }

    int getKey() { return key; }

    void display() { printf("%4d", key); }
};

#endif