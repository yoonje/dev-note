#ifndef DATASTRUCTURE_WEIGHTADJMATGRAPH_H
#define DATASTRUCTURE_WEIGHTADJMATGRAPH_H

#include "AdjmatGraph.h"
#include <cstdio>

#define INF 9999

class WeightAdjmatGraph : public AdjmatGraph {
public:

    WeightAdjmatGraph() { reset(); }

    void reset() {
        size = 0;
        for (int i = 0; i < MAX_VTXS; i++)
            for (int j = 0; j < MAX_VTXS; j++)
                setEdge(i, j, 9999);
    }

    void insertEdge(int u, int v, int weight) {
        if (weight >= INF)
            weight = INF;
        setEdge(u, v, weight);
        setEdge(v, u, weight);
    }

    bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }

    void display() {
        printf("인접행렬로 표현한 가중치 그래프\n");
        printf("Vertex size = %d\n", size);
        for (int i = 0; i < size; i++) {
            printf("%c   ", getVertex(i));
            for (int j = 0; j < size; j++) {
                printf("%9d ", getEdge(i, j));
            }
            printf("\n");
        }
    };
};


#endif //DATASTRUCTURE_WEIGHTADJMATGRAPH_H
