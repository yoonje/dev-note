#include "HashMap.h"
#include "Record.h"
#include "hashFunction.h"
#include <cstdio>
#include <cstring>

HashMap::HashMap() {
    reset();
}

void HashMap::reset() {
    for (int i = 0; i < TABLE_SZIE; i++) {
        table[i].reset();
    }
}

void HashMap::display() {
    for (int i = 0; i < TABLE_SZIE; i++) {
        printf("[%2d] ", i);
        table[i].display();
    }
}

void HashMap::addLinearProb(char *key, char *value) {
    int i, hashValue;
    hashValue = i = hashFunction(key);
    while (table[i].isEmpty() == false) {
        if (table[i].equal(key)) {
            printf("[%s] 탐색 키가 중복되었습니다.\n", key);
            return;
        }
        i = (i + 1) % TABLE_SZIE;
        if (i == hashValue) {
            printf("[%s] 테이블이 가득찼습니다.\n", key);
            return;
        }
    }
    table[i].set(key, value);
}

Record *HashMap::searchLinearProb(char *key) {
    int i, hashValue;
    hashValue = i = hashFunction(key);
    while (table[i].isEmpty() == false) {
        if (table[i].equal(key)) {
            printf("[%s] 탐색 성공[%d]", key, i);
            table[i].display();
            return table + i;
        }
        i = (i + 1) % TABLE_SZIE;
        if (i == hashValue)
            break;
    }
    printf("[%s] 탐색 실패: 찾는 값이 테이블에 없음\n", key);
    return NULL;
}