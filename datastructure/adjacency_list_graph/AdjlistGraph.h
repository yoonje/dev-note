#ifndef DATASTRUCTURE_ADJLISTGRAPH_H
#define DATASTRUCTURE_ADJLISTGRAPH_H

#include "Node.h"

#define MAX_VTXS 256

class AdjlistGraph {
protected:
    int size;
    char vertices[MAX_VTXS];
    Node *adj[MAX_VTXS];
public:
    AdjlistGraph() : size(0) {}

    ~AdjlistGraph() { reset(); }

    void reset() {
        for (int i = 0; i < size; i++) {
            if (adj[i] != NULL)
                delete adj[i];
        }
        size = 0;
    }

    bool isEmpty() { return (size == 0); }

    bool isFull() { return (size > MAX_VTXS); }

    char getVertex(int i) { return vertices[i]; }

    Node* adjacent(int v) { return adj[v]; }

    void insertVertex(char val);

    void insertEdge(int u, int v);

    void display();

};


#endif //DATASTRUCTURE_ADJLISTGRAPH_H
