#include "MaxHeap.h"

int main() {
    MaxHeap hp;

    hp.insert(10);
    hp.insert(20);
    hp.insert(200);
    hp.insert(1);
    hp.insert(20);
    hp.insert(20);
    hp.insert(5);
    hp.insert(7);
    hp.insert(30);
    hp.display();

    hp.remove();
    hp.remove();
    hp.remove();
    hp.display();

    return 0;
}