#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <stdint.h>

uint64_t nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    uint64_t nsec = (t_stop->tv_nsec - t_start->tv_nsec);
    uint64_t sec = (t_stop->tv_sec - t_start->tv_sec);
    return nsec + sec * 1000000000;
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
    for (int i = 1; i < n; i++) {
        int j = i - 1; 
        int key = arr[i];
        while (arr[j] > key && j >= 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

uint64_t benchmark(int* arr, int size){
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
        uint64_t wall = benchmark(arr, size);
        printf("%d elements -> %lu ns\n", size, wall);
        free(arr);
    }
    return 0;
}
