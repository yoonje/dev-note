#include "LinkedQueue.h"

void LinkedQueue::enqueue(Node *p) {
    if (isEmpty())
        front = rear = p;
    else {
        rear->setLink(p);
        rear = p;
    }
}

void LinkedQueue::enqueue(int e) {
    Node *p =  new Node(e);
    if (isEmpty())
        front = rear = p;
    else {
        rear->setLink(p);
        rear = p;
    }
}

Node *LinkedQueue::deque() {
    if(isEmpty())
        return NULL;
    Node* p =front;
    front = front->getLink();
    if (front==NULL)
        rear =NULL;
    return p;
}

void LinkedQueue::display() {
    for(Node* p = front; p != NULL ; p=p->getLink()){
        p->display();
    }
    printf("\n");
}