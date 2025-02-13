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

void array_append(int* a, int* b, int asize, int bsize){
    int* narr = malloc(sizeof(int)*(asize+bsize));
    for(int i=0; i < (asize+bsize); i++){
        if (i < asize){
            narr[i] = a[i];
            continue;
        }
        narr[i] = b[i-asize];
    }
}

long benchmark(int* a, int* b, int asize, int bsize){
    struct timespec t_start, t_stop;
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    array_append(a,b, asize, bsize);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    long wall = nano_seconds(&t_start, &t_stop);
    return wall;
}

int *random(int n) {
    int *array = (int*)malloc(n*sizeof(int));
    // this ensures we reset the random seed
    // to get truly random ints
    for (int i = 0; i < n ; i++) {
        array[i] = (rand() % (n*10))+1;
    }
    return array;
}

int main()
{
    srand(time(NULL));
    int n = 6;
    for (int i = 1; i < n+1 ; i++) {
        int t = 100;
        int c = 0;
        long *r = malloc(sizeof(long) * t);   
        int size = (int)pow(10, i);
        while(t!=0){
            int *a = random(size); 
            int *b = random(size); 
            long wall = benchmark(a, b, size, size);
            r[c++] = wall;
            t--;
        }
        long sum = 0;
        long small = LONG_MAX;
        for (int i = 0; i < c; i++) {
            sum += r[i]; 
            if (r[i] < small) small = r[i];
        }

        long avg = sum / c;
        printf("%d (array a) app. %d (array b) -> avg (%ld ns) min (%ld ns)\n", size, size, avg, small);
    }
    return 0;
}
