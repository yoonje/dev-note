#include "AdjmatGraph.h"
#include <cstdio>

void AdjmatGraph::reset() {
    size = 0;
    for (int i = 0; i < MAX_VTXS; i++)
        for (int j = 0; j < MAX_VTXS; j++)
            setEdge(i, j, 0);
}

void AdjmatGraph::insertVertex(char name) {
    if (!isFull())
        vertices[size++] = name;
    else
        printf("그래프의 정점 개수 초과입니다.\n");
}

void AdjmatGraph::insertEdge(int u, int v) {
    setEdge(u, v, 1);
    setEdge(v, u, 1);
}


void AdjmatGraph::display() {
    printf("인접행렬로 표현한 그래프\n");
    printf("Vertex size = %d\n", size);
    for (int i = 0; i < size; i++) {
        printf("%c   ", getVertex(i));
        for (int j = 0; j < size; j++) {
            printf("%3d", getEdge(i, j));
        }
        printf("\n");
    }
}