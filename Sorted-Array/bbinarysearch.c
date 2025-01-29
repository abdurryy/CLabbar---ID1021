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

bool binary_search(int array[], int length, int key) {
    int first = 0;
    int last = length - 1;
    while (first <= last) {
        int index = first + (last - first) / 2;
        if (array[index] == key) {
            return true;
        }
        if (array[index] < key) {
            first = index + 1;
        } else {
            last = index - 1;
        }
    }
    return false;
}

int *sorted(int n) {
    int *array = (int*)malloc(n*sizeof(int));
    // this ensures we reset the random seed
    // to get truly random ints
    srand(time(NULL)); 
    int nxt = 0;
    for (int i = 0; i < n ; i++) {
        nxt += (rand() % 10)+1;
        array[i] = nxt;
    }
    return array;
}

long benchmark(int* arr, int size, int key){
    struct timespec t_start, t_stop;
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    binary_search(arr,size,key);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    long wall = nano_seconds(&t_start, &t_stop);
    return wall;
}

int main(){
    printf("Benchmarking random sized arrays. \n");
    int n = 6;
    for (int i = 1; i < n+1 ; i++) {
        srand(time(NULL));
        int size = (int)pow(10, i);
        int *arr = sorted(size);
        int key = (int)(((rand() % size*10)+1)/2);
        long wall = benchmark(arr, size, key);
        printf("%d element(s) %ld ns\n", (int)pow(10, i),wall);
    }
}