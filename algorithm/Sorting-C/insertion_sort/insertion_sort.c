#include "insertion.h"

void insertion_sort(int *arr, int num) {
    int i, j, temp;
    for (i = 1; i < num; i++) {
        temp = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = temp;
    }
}