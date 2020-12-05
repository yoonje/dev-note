#ifndef DATASTRUCTURE_NODE_H
#define DATASTRUCTURE_NODE_H
#include <cstdlib>
#include "Record.h"

class Node : public Record {
private:
    Node *link;
public:
    Node(char *key, char *val) : Record(key, val), link(NULL) {}

    Node *getLink() { return link; }

    void setLink(Node *next) { link = next; }
};

#endif //DATASTRUCTURE_NODE_H
