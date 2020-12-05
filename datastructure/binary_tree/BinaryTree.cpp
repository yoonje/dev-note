#include "BinaryTree.h"
#include <cstdio>

void BinaryTree::inorder() {
    printf("\n inorder: ");
    inorder(root);
}

void BinaryTree::inorder(BinaryNode *node) {
    if (node != NULL) {
        if (node->getLeft() != NULL)
            inorder(node->getLeft());
        printf(" [%c] ", node->getData());
        if (node->getRight() != NULL)
            inorder(node->getRight());
    }
}

void BinaryTree::preorder() {
    printf("\n preorder: ");
    preorder(root);
}

void BinaryTree::preorder(BinaryNode *node) {
    if (node != NULL) {
        printf(" [%c] ", node->getData());
        if (node->getLeft() != NULL)
            inorder(node->getLeft());
        if (node->getRight() != NULL)
            inorder(node->getRight());
    }
}

void BinaryTree::postorder() {
    printf("\n postorder: ");
    postorder(root);
}

void BinaryTree::postorder(BinaryNode *node) {
    if (node != NULL) {
        if (node->getLeft() != NULL)
            inorder(node->getLeft());
        if (node->getRight() != NULL)
            inorder(node->getRight());
        printf(" [%c] ", node->getData());
    }
}

int BinaryTree::getHeight(BinaryNode *node) {
    if (node == NULL)
        return 0;
    int hLeft = getHeight(node->getLeft());
    int hRight = getHeight(node->getRight());
    return (hLeft > hRight) ? hLeft + 1 : hRight + 1;
}

int BinaryTree::evaluate(BinaryNode *node) {
    if (node == NULL)
        return 0;
    if (node->isLeaf())
        return node->getData();
    else {
        int op1 = evaluate(node->getLeft());
        int op2 = evaluate(node->getRight());
        switch (node->getData()) {
            case '+':
                return op1 + op2;
            case '-':
                return op1 - op2;
            case '*':
                return op1 * op2;
            case '/':
                return op1 / op2;
        }
        return 0;
    }
}

int BinaryTree::getCount(BinaryNode *node) {
    if (node == NULL)
        return 0;
    return 1 + getCount(node->getLeft()) + getCount(node->getRight());
}


int BinaryTree::getLeafCount(BinaryNode *node) {
    if (node == NULL)
        return 0;
    if (node->isLeaf())
        return 1;
    else return getLeafCount(node->getLeft()) + getLeafCount(node->getRight());
}