#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
    (t_stop->tv_sec - t_start->tv_sec)*1000000000;
}

int *random(int n) {
    int *array = (int*)malloc(n*sizeof(int));
    srand(time(NULL)); 
    for (int i = 0; i < n ; i++) {
        array[i] = (rand() % (n*10))+1;
    }
    return array;
}

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}


long benchmark(int* arr, int size){
    struct timespec t_start, t_stop;
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    sort(arr, size);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    return nano_seconds(&t_start, &t_stop);
}

int main() {
    printf("Benchmarking random sized arrays.\n");
    int n = 6; // Number of tests
    for (int i = 1; i <= n; i++) {
        int size = (int)pow(10, i);
        int *arr = random(size);
        long wall = benchmark(arr, size);
        printf("%d elements -> %ld ns\n", size, wall);
        free(arr);
    }
    return 0;
}