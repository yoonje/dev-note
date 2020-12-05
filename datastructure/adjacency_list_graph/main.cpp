#include"AdjlistGraph.h"
#include <cstdio>

int main() {
    AdjlistGraph g;

    for (int i = 0; i < 4; i++) {
        g.insertVertex('A' + i);
    }
    g.insertEdge(0, 3);
    g.insertEdge(1, 2);
    g.insertEdge(0, 1);
    g.insertEdge(2, 3);
    g.display();

    return 0;

}