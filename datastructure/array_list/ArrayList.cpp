#include "ArrayList.h"
#include <cstdio>

void ArrayList::insert(int pos, int e) {
    if (!isFull() && pos >= 0 && pos <= length) {
        for (int i = length; i > pos; i--)
            data[i] = data[i - 1];
        data[pos] = e;
        length++;
    }
}

void ArrayList::remove(int pos) {
    if (!isEmpty() && 0 <= pos && pos < length) {
        for (int i = pos + 1; i < length; i++) {
            data[i - 1] = data[i];
        }
        length--;
    } else
        printf("empty or position error");
}


bool ArrayList::find(int item) {
    for (int i = 0; i < length; i++) {
        if (data[i] == item)
            return true;
        return false;
    }
}

void ArrayList::display() {
    printf("total items = %2d\n", size());
    for (int i = 0; i < size(); i++) {
        printf("%2d ", data[i]);
    }
    printf("\n");
}