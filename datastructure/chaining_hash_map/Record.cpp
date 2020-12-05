#include "Record.h"
#include <cstdio>
#include <cstring>

#define KEY_SIZE 64
#define VALUE_SIZE 64

void Record::set(char *k, char *v) {
    strcpy(key, k);
    strcpy(value, v);
}

bool Record::equal(char *k) {
    return strcmp(k, key) == 0;
}

void Record::display() {
    printf("%20s = %s\n", key, value);
}