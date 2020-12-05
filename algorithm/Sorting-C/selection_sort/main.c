#include <stdio.h>
#include <stdlib.h>
#include "selection.h"

#define ARR_SIZE 10

int main() {

    int array[] = {10, 203, 22, 11, 411, -1, 11, 0, -5, 2};
    printf("selection sorting!\n");
    selection_sort(array, ARR_SIZE);
    for (int i = 0; i < ARR_SIZE; i++) {
        printf("%d ", array[i]);
    }
    return 0;
}
