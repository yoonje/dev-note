#ifndef DATASTRUCTURE_ADJMATGRAPH_H
#define DATASTRUCTURE_ADJMATGRAPH_H

#define MAX_VTXS 256

class AdjmatGraph {
protected:
    int size;
    char vertices[MAX_VTXS];
    int adj[MAX_VTXS][MAX_VTXS];
public:
    AdjmatGraph() { reset(); }

    char getVertex(int i) { return vertices[i]; }

    int getEdge(int i, int j) { return adj[i][j]; }

    void setEdge(int i, int j, int val) { adj[i][j] = val; }

    bool isEmpty() { return size == 0; }

    bool isFull() { return size >= MAX_VTXS; }

    void reset();

    void insertVertex(char name);

    void insertEdge(int u, int v);

    void display();

};


#endif //DATASTRUCTURE_ADJMATGRAPH_H
