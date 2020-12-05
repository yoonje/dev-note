#include <stdio.h>
#include <stdlib.h>
#include "merge.h"

#define ARR_SIZE 10

int main() {

    int array[] = {10, 203, 22, 11, 411, -1, 11, 0, -5, 2};
    printf("merge sorting!\n");
    merge_sort(array, 0, ARR_SIZE - 1);
    for (int i = 0; i < ARR_SIZE; i++) {
        printf("%d ", array[i]);
    }
    return 0;
}
