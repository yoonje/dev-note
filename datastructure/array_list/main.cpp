#include "./ArrayList.h"

int main(void)
{
    ArrayList list;

    list.insert(0,10);
    list.insert(0,20);
    list.insert(3,50);
    list.insert(0,20);
    list.insert(0,10);
    list.display();

    list.remove(0);
    list.display();

    list.remove(list.size()-1);
    list.display();

    list.clear();
    list.display();

    return 0;
}