#include "bubble.h"

void bubble_sort(int list[], int n) {
    int i, j, temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1; j++) {
            if (list[j] > list[j + 1]) {
                swap(&list[j], &list[j + 1]);
            }
        }
    }
}

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}