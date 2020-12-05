#ifndef DATASTRUCTURE_BINARYSRCHTREE_H
#define DATASTRUCTURE_BINARYSRCHTREE_H

#include <iostream>

using namespace std;
template<typename T>
struct Node {
    Node *left;
    Node *right;
    T value;
};

template<typename T>
class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {};

    ~BinarySearchTree() {};

    void AddNode(T _value);

    bool SearchValue(T _value);

    void RemoveNode(T _value);

    void Display();

private:
    Node<T> *root;
    Node<T> *tail;

    void Inorder(Node<T> *current) {
        if (current != nullptr) {
            Inorder(current->left);
            cout << current->value << " ";
            Inorder(current->right);
        }
    }

    Node<T> *SearchMaxNode(Node<T> *node) {
        if (node == NULL) return NULL;
        while (node->right != NULL) { node = node->right; }
        return node;
    }

    Node<T> *RemoveSeqence(Node<T> *node, T _vaule);
};

template<typename T>
Node<T> *BinarySearchTree<T>::RemoveSeqence(Node<T> *node, T _vaule) {
    if (node == nullptr) return node;
    else if (node->value > _vaule)node->left = RemoveSeqence(node->left, _vaule);
    else if (node->value < _vaule)
        node->right = RemoveSeqence(node->right, _vaule);
    else {
        Node<T> *ptr = node;
        if (node->right == nullptr && node->left == nullptr) {
            delete node;
            node = nullptr;
        }
        else if (node->right == nullptr) {
            node = node->left;
            delete ptr;
        }
        else if (node->left == nullptr) {
            node = node->right;
            delete ptr;
        }
        else {
            ptr = SearchMaxNode(node->left);
            node->value = ptr->value;
            node->left = RemoveSeqence(node->left, ptr->value);
        }
    }
    return node;
}

template<typename T>
void BinarySearchTree<T>::RemoveNode(T _value) {
    Node<T> *ptr = root;
    RemoveSeqence(ptr, _value);
}

template<typename T>
void BinarySearchTree<T>::Display() { Inorder(root); }

template<typename T>
bool BinarySearchTree<T>::SearchValue(T _value) {
    Node<T> *ptr = root;
    Node<T> *tmpRoot = nullptr;
    while (ptr != nullptr) {
        if (ptr->value == _value) {
            cout << _value << "을 찾았습니다." << endl;
            return true;
        }
        else if (ptr->value > _value) ptr = ptr->left; else ptr = ptr->right;
    }
    cout << _value << "을 찾지 못했습니다." << endl;
    return false;
}

template<typename T>
void BinarySearchTree<T>::AddNode(T _value) {
    Node<T> *node = new Node<T>();
    Node<T> *tmpRoot = nullptr;
    node->value = _value;
    if (root == nullptr) root = node;
    else {
        Node<T> *ptr = root;
        while (ptr != nullptr) {
            tmpRoot = ptr;
            if (node->value < ptr->value) { ptr = ptr->left; } else { ptr = ptr->right; }
        }
        if (node->value < tmpRoot->value) tmpRoot->left = node; else tmpRoot->right = node;
    }
}


#endif //DATASTRUCTURE_BINARYSRCHTREE_H
