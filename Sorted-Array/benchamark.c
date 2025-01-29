#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool unsorted_search(int array[], int length, int key) {
    for (int index = 0; index < length ; index++) {
        if (array[index] == key) {
            
            return true;
        }
    }
    return false;
}

int *sorted(int n) {
    int *array = (int*)malloc(n*sizeof(int));
    int nxt = 0;
    for (int i = 0; i < n ; i++) {
        nxt += rand()%10 + 1;
        array[i] = nxt;
    }
    return array;
}

int main()
{
    int *arr = sorted(1000000);
    bool f = unsorted_search(arr,1000000,999999);
    printf("%s\n", f ? "true" : "false");
    free(arr);
    return 0;
}

