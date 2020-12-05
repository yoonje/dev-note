#include"WeightAdjmatGraph.h"

int main() {
    WeightAdjmatGraph g;

    for (int i = 0; i < 4; i++) {
        g.insertVertex('A' + i);
    }
    g.insertEdge(0, 3, 120);
    g.insertEdge(1, 2, -100);
    g.insertEdge(0, 1, 50);
    g.insertEdge(2, 3, 100);
    g.display();
    return 0;
}