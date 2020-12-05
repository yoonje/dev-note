#ifndef DATASTRUCTURE_HASHMAP_H
#define DATASTRUCTURE_HASHMAP_H
#include "Record.h"
#define TABLE_SIZE 13

class HashMap {
private:
    Record table[TABLE_SIZE];
public:
    HashMap();

    void reset();

    void display();

    void addLinearProb(char *key, char *value);

    Record* searchLinearProb(char*key);
};


#endif //DATASTRUCTURE_HASHMAP_H
