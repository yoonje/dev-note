#include "BinarySrchTree.h"

int main() {
    BinarySearchTree<int> *BST = new BinarySearchTree<int>();
    BST->AddNode(1);
    BST->AddNode(3);
    BST->AddNode(6);
    BST->AddNode(9);
    BST->AddNode(13);
    BST->AddNode(22);
    BST->AddNode(17);
    BST->AddNode(10);
    BST->AddNode(2);
    BST->Display();
    cout << endl;
    BST->SearchValue(4);
    BST->SearchValue(17);
    cout << endl;
    BST->RemoveNode(17);
    BST->RemoveNode(9);
    BST->RemoveNode(6);
    BST->RemoveNode(3);
    BST->Display();
    cout << endl;
    return 0;
}
