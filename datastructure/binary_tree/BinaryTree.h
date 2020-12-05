#ifndef DATASTRUCTURE_BINARYTREE_H
#define DATASTRUCTURE_BINARYTREE_H

#include "BinaryNode.h"

class BinaryTree {
private:
    BinaryNode *root;
public:
    BinaryTree(): root(NULL) {}

    void setRoot(BinaryNode *node) { root = node; }

    BinaryNode *getRoot() { return root; }

    bool isEmpty() { return root == NULL; }

    void inorder();

    void inorder(BinaryNode *node);

    void preorder();

    void preorder(BinaryNode *node);

    void postorder();

    void postorder(BinaryNode *node);

    int getCount() { return isEmpty() ? 0 : getCount(root); }

    int getCount(BinaryNode *node);

    int getHeight() { return isEmpty() ? 0 : getHeight(root); }

    int getHeight(BinaryNode *node);

    int getLeafCount() { return isEmpty() ? 0 : getLeafCount(root); }

    int getLeafCount(BinaryNode *node);

    int evaluate() { return evaluate(root); }

    int evaluate(BinaryNode *node);

};


#endif //DATASTRUCTURE_BINARYTREE_H
