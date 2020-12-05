#ifndef DATASTRUCTURE_CIRCULARQUEUE_H
#define DATASTRUCTURE_CIRCULARQUEUE_H
#define MAX_QUEUE_SIZE 100

inline void error(char *message);

class CircularQueue {
protected:
    int front;
    int rear;
    int data[MAX_QUEUE_SIZE];
public:
    CircularQueue() { front = rear = 0; }

    bool isEmpty() { return front == rear; }

    bool isFull() { return (rear + 1) % MAX_QUEUE_SIZE == front; }

    void enqueue(int val);

    int deque();

    int peek();

    void display();
};


#endif //DATASTRUCTURE_CIRCULARQUEUE_H
