#include "heap.h"

void heap_sort(int *ar, int size) {
    int count = 0;
    int temp = 0;

    build_max_heap(ar, size);

    for (count = size - 1; count > 0; count--) {
        temp = ar[count];
        ar[count] = ar[0];
        ar[0] = temp;

        max_heapify(ar, count, 0);
    }
}

void build_max_heap(int *A, int s) {
    int i = 0;

    for (i = (s / 2) - 1; i >= 0; i--) {
        max_heapify(A, s, i);
    }
}

void max_heapify(int *A, int size, int index) {
    int left = index * 2;
    int right = index * 2 + 1;
    int largest = index;
    int temp = 0;

    if (left < size && A[left] > A[index]) {
        largest = left;
    }

    if (right < size && A[right] > A[largest]) {
        largest = right;
    }

    if (largest != index) {
        temp = A[largest];
        A[largest] = A[index];
        A[index] = temp;

        max_heapify(A, size, largest);
    }
}