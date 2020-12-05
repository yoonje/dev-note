#include "CircularQueue.h"

int main() {
    CircularQueue que;
    for (int i = 1; i < 10; i++) {
        que.enqueue(i);
    }
    que.display();
    que.deque();
    que.deque();
    que.deque();
    que.deque();
    que.display();

    return 0;
}