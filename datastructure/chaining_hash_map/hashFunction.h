#ifndef DATASTRUCTURE_HASGFUNCTIONS_H
#define DATASTRUCTURE_HASGFUNCTIONS_H

#define TABLE_SIZE 13

inline int trasform(char *key) {
    int number = 0;
    while (*key)
        number += (*key++);
    return number;
}

inline int hashFunction(char *key) {
    return trasform(key) % TABLE_SIZE;
}

#endif //DATASTRUCTURE_HASGFUNCTIONS_H
