#include "MaxHeap.h"

void MaxHeap::insert(int key) {
    if (isFull())
        return;
    int i = ++size;

    while (i != 1 && key > getParent(i).getKey()) {
        node[i] = getParent(i);
        i /= 2;
    }
    node[i].setKey(key);

}

HeapNode MaxHeap::remove() {
    if (isEmpty())
        return NULL;
    HeapNode item = node[1];
    HeapNode last = node[size--];

    int temp_parent = 1;
    int temp_child = 2;

    while (temp_child <= size) {
        if (temp_child < size && getLeft(temp_parent).getKey() < getRight(temp_parent).getKey())
            temp_child++;
        if (last.getKey() >= node[temp_child].getKey())
            break;
        node[temp_parent] = node[temp_child];
        temp_parent = temp_child;
        temp_child *= 2;
    }

    node[temp_parent] = last;
    return item;
}