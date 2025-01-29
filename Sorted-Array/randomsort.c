#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
    (t_stop->tv_sec - t_start->tv_sec)*1000000000;
}

long benchmark(){
    struct timespec t_start, t_stop;
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    // operation here
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    long wall = nano_seconds(&t_start, &t_stop);
    return wall;
}

bool unsorted_search(int array[], int length, int key) {
    for (int index = 0; index < length ; index++) {
        printf("%d \n", array[index]);
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



int main()
{
    int *arr = random(10);
    bool f = unsorted_search(arr,10,1);
    printf("%s\n", f ? "true" : "false");
    free(arr);
    return 0;
}

