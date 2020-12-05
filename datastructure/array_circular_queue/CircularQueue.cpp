#include "CircularQueue.h"
#include <cstdio>
#include <cstdlib>

inline void error(char *message) {
    printf("%s\n", message);
    exit(1);
}

void CircularQueue::enqueue(int val) {
    if (isFull())
        error("포화 상태");
    else {
        rear = (rear + 1) % MAX_QUEUE_SIZE;
        data[rear] = val;
    }
}

int CircularQueue::deque() {
    if (isEmpty())
        error("공백 상태");
    else {
        front = (front + 1) % MAX_QUEUE_SIZE;
        return data[front];
    }
}

int CircularQueue::peek() {
    if (isEmpty())
        error("공백 상태");
    else
        return data[(front + 1) % MAX_QUEUE_SIZE];
}

void CircularQueue::display() {
    int maxi = (front < rear) ? rear : rear + MAX_QUEUE_SIZE;
    for (int i = front + 1; i <= maxi; i++) {
        printf("%2d ", data[i % MAX_QUEUE_SIZE]);
    }
    printf("\n");
}