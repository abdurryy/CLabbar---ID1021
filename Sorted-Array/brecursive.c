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

bool recursive(int array[], int length, int key, int first, int last) {
    if (first > last) {
        return false; 
    }
    int index = first + (last - first) / 2; 
    if (array[index] == key) {
        return true; 
    }
    if (array[index] < key) {
        return recursive(array, length, key, index + 1, last); 
    } else {
        return recursive(array, length, key, first, index - 1); 
    }
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
    int first = 0;
    int last = size - 1;
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    recursive(arr,size,key,first,last);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    long wall = nano_seconds(&t_start, &t_stop);
    return wall;
}

int main(){
    printf("Benchmarking sorted sized arrays. \n");
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