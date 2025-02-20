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

void merge(int *org, int *aux, int lo, int mid, int hi) {
    for (int k = lo; k <= hi; k++) {
        aux[k] = org[k];
    }
    int i = lo;      
    int j = mid + 1; 
    for (int k = lo; k <= hi; k++) {
        if (i > mid) {
            org[k] = aux[j++];
        } else if (j > hi) {
            org[k] = aux[i++];
        } else if (aux[i] <= aux[j]) {
            org[k] = aux[i++];
        } else {
            org[k] = aux[j++];
        }
    }
}

void sort(int *org, int *aux, int lo, int hi) {
    if (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        sort(org, aux, lo, mid);     
        sort(org, aux, mid + 1, hi);  
        merge(org, aux, lo, mid, hi); 
    }
}

uint64_t benchmark(int* arr, int size){
    int *aux = (int*)malloc(size * sizeof(int));
    struct timespec t_start, t_stop;
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    sort(arr, aux, 0, size - 1);
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
