#ifndef _NODE_H
#define _NODE_H

class Node {
private:
    Node *link;
    int data;
public:
    Node(int val = 0) : data(val) {}

    Node *getLink() { return link; }

    void setLink(Node *next) { link = next; }

    void display();

    bool hasData(int val) { return data == val; }

    void insertNext(Node *n);

    Node *removeNext();
};

#endif