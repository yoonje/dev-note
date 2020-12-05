#include <cstdio>
#include <cstdlib>
#include "ArrayStack.h"

inline void error(char *message) {
    printf("%s\n", message);
    exit(1);
}

void ArrayStack::push(int e) {
    if (isFull())
        error("스택 포화");
    data[++top] = e;
}

int ArrayStack::pop() {
    if (isEmpty())
        error("스택 공백");
    return data[top--];
}

int ArrayStack::peek() {
    if (isEmpty())
        error("스택 공백");
    return data[top];
}

void ArrayStack::display() {
    printf("스택 항목의 수 = %2d", top + 1);
    printf("\n");
    for (int i = 0; i <= top; i++) {
        printf("%2d ", data[i]);
    }
    printf("\n");
}