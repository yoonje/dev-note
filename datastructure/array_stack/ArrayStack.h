#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

const int MAX_STACK_SIZE = 20;

class ArrayStack {
private:
    int top;
    int data[MAX_STACK_SIZE];
public:
    ArrayStack() { top = -1; }

    ~ArrayStack() {}

    bool isEmpty() { return top == -1; }

    bool isFull() { return top == MAX_STACK_SIZE - 1; }

    void push(int e);

    int pop();

    int peek();

    void display();
};

#endif
