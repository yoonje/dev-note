#include "HashChainMap.h"
#include <cstdio>
#include <cstdlib>

void HashChainMap::display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%2d] ", i);
        for (Node *p = table[i]; p != NULL; p = p->getLink())
            printf("%10s", p->getKey());
        printf("\n");
    }
}

void HashChainMap::addRecord(Node *n) {
    int hashValue = hashFunction(n->getKey());
    for (Node *p = table[hashValue]; p != NULL; p = p->getLink()) {
        if (p->equal(n->getKey())) {
            printf("이미 탐색키가 저장되어 있음\n");
            delete n;
            return;
        }
    }
    n->setLink(table[hashValue]);
    table[hashValue] = n;
}

void HashChainMap::searchNode(char *key) {
    int hashValue = hashFunction(key);
    for (Node *p = table[hashValue]; p != NULL; p = p->getLink()) {
        if (p->equal(key)) {
            printf("탐색 성공 ");
            p->display();
            return;
        }
    }
    printf("탐색 실패: %s\n", key);
}