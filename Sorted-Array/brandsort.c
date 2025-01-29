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

bool search_random_array(int array[], int length, int key) {
    for (int index = 0; index < length ; index++) {
        if (array[index] == key) {
            return true;
        }
    }
    return false;
}

int *random(int n) {
    int *array = (int*)malloc(n*sizeof(int));
    // this ensures we reset the random seed
    // to get truly random ints
    srand(time(NULL)); 
    for (int i = 0; i < n ; i++) {
        array[i] = (rand() % (n*10))+1;
    }
    return array;
}

long benchmark(int* arr, int size){
    struct timespec t_start, t_stop;
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    search_random_array(arr,size, 0);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    long wall = nano_seconds(&t_start, &t_stop);
    return wall;
}

int main(){
    printf("Benchmarking random sized arrays. \n");
    int n = 6;
    for (int i = 1; i < n+1 ; i++) {
        int size = (int)pow(10, i);
        int *arr = random(size);
        long wall = benchmark(arr, size);
        printf("%d element(s) -> %ld ns\n", (int)pow(10, i),wall);
    }
}