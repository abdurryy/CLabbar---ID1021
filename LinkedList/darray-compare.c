#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <limits.h>  // For LONG_MAX
#include <string.h>  // For memcpy

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
    (t_stop->tv_sec - t_start->tv_sec)*1000000000;
}

void array_append(int* a, int* b, int asize, int bsize, int* result) {
    // Use memcpy to copy elements from both arrays into result
    memcpy(result, a, asize * sizeof(int));
    memcpy(result + asize, b, bsize * sizeof(int));
}

long benchmark(int* a, int* b, int asize, int bsize, int* result) {
    struct timespec t_start, t_stop;
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    array_append(a, b, asize, bsize, result);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    return nano_seconds(&t_start, &t_stop);
}

int *random(int n) {
    int *array = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        array[i] = (rand() % (n * 10)) + 1;
    }
    return array;
}

int main() {
    srand(time(NULL));
    int n = 6;
    for (int i = 1; i <= n; i++) {
        int t = 100;
        long *r = malloc(sizeof(long) * t);
        int size = (int)pow(10, i);
        int *a = random(size); // Pre-allocate arrays once
        int *b = random(size);
        int *result = malloc(sizeof(int) * (2 * size)); // Allocate result array only once
        
        for (int j = 0; j < t; j++) {
            long wall = benchmark(a, b, size, size, result);
            r[j] = wall;
        }

        long sum = 0;
        long small = LONG_MAX;
        for (int k = 0; k < t; k++) {
            sum += r[k];
            if (r[k] < small) small = r[k];
        }

        long avg = sum / t;
        printf("%d (array a) app. %d (array b) -> avg (%ld ns) min (%ld ns)\n", size, size, avg, small);
        
        free(a);  // Free arrays after use
        free(b);
        free(result);
        free(r);  // Free the result array
    }
    return 0;
}
