#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

typedef struct cell {
    int value;
    struct cell *tail;
} cell;

typedef struct linked {
    cell *first;
} linked;

linked *linked_create() {
    linked *new = (linked*)malloc(sizeof(linked));
    new->first = NULL;
    return new;
}

void linked_free(linked *lnk) {
    cell *nxt = lnk->first;
    while (nxt != NULL) {
    cell *tmp = nxt->tail;
    free(nxt);
    nxt = tmp;
    }
    free(lnk);
}

void linked_add(linked *lnk, int item) {
    cell *n = (cell *)malloc(sizeof(cell));
    n->value = item;
    n->tail = lnk->first;
    lnk->first = n;
}

int linked_length(linked *lnk) {
    int count = 0;
    cell *curr = lnk->first;
    while (curr != NULL) {
        count++;
        curr = curr->tail;
    }
    return count;
}

bool linked_find(linked *lnk, int item) {
    cell *curr = lnk->first;
    while (curr != NULL) {
        if (curr->value == item) {
            return true; 
        }
        curr = curr->tail;
    }
    return false; 
}

void linked_remove(linked *lnk, int item) {
    cell *curr = lnk->first;
    cell *prev = NULL;
    while (curr != NULL && curr->value != item) {
        prev = curr;
        curr = curr->tail;
    }
    if (curr == NULL) {
        return;
    }
    if (prev == NULL) {
        lnk->first = curr->tail;
    } else {
        prev->tail = curr->tail;
    }
    free(curr);
}

void linked_append(linked *a, linked *b) {
    if (a->first == NULL) {
        a->first = b->first;
        return;
    }
    cell *nxt = a->first;
    while (nxt->tail != NULL) {
        nxt = nxt->tail;
    }
    nxt->tail = b->first;
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

linked *linked_init(int size, int *arr) {
    linked *a = linked_create(); 
    for (int i = 0; i < size; i++) {
        linked_add(a, arr[i]);
    }
    return a;
}

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
    (t_stop->tv_sec - t_start->tv_sec)*1000000000;
}

long benchmark(linked* a,linked* b){
    struct timespec t_start, t_stop;
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    linked_append(a,b);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    long wall = nano_seconds(&t_start, &t_stop);
    return wall;
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
        int fsize = 1000;
        int *darr = random(size); 
        int *arr = random(fsize);  
        while(t!=0){
            int *arr = random(size); 
            linked *a = linked_init(size, darr);
            linked *b = linked_init(fsize, arr);
            long wall = benchmark(a, b);
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
        printf("%d (linked a) app. %d (linked b) -> avg (%ld ns) min (%ld ns)\n", size, fsize, avg, small);
    }
    return 0;
}