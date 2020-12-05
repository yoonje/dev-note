#ifndef _ARRAY_LIST_H
#define _ARRAY_LIST_H
#define MAX_LIST_SIZE 100

class ArrayList {
private:
    int data[MAX_LIST_SIZE];
    int length;
public:
    ArrayList(void) { length = 0; }

    void insert(int pos, int e);

    void remove(int pos);

    int getEntry(int pos) { return data[pos]; }

    bool isEmpty() { return length == 0; }

    bool isFull() { return length == MAX_LIST_SIZE; }

    bool find(int item);

    void replace(int pos, int e) {
        data[pos] = e;
    }

    int size() { return length; }

    void display();

    void clear() { length = 0; }
};

#endif