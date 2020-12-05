#include "Node.h"
#include "hashFunction.h"

class HashChainMap {
private:
    Node *table[TABLE_SIZE];
public:
    HashChainMap() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = NULL;
        }
    }
    void display();
    void addRecord(Node *n);
    void searchNode(char *key);
};