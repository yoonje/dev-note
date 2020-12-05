#include "AdjlistGraph.h"
#include <cstdio>

void AdjlistGraph::insertVertex(char val) {
    if (!isFull()) {
        vertices[size] = val;
        adj[size++] = NULL;
    } else
        printf("Error: 그래프 정점의 개수가 초과되었습니다.\n");
}

void AdjlistGraph::insertEdge(int u, int v) {
    adj[u] = new Node(v, adj[u]);
    adj[v] = new Node(u, adj[v]);
}

void AdjlistGraph::display() {
    printf("인접리스트로 표현한 그래프\n");
    printf("Vertex size = %d\n", size);
    for (int i = 0; i < size; i++) {
        printf("%c  ", getVertex(i));
        for(Node* v=adj[i]; v !=NULL; v=v->getLink())
            printf(" %c", getVertex(v->getId()));
        printf("\n");
    }
}