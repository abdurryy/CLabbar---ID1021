#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

typedef struct queue {
    int _first;
    int _last;
    int _elements;
    int _size;
    int *_items;
} queue;

queue *create_queue(int size) {
    queue *q = (queue*)malloc(sizeof(queue));
    q->_first = 0;
    q->_last = 0;
    q->_elements = 0;
    q->_size = size;
    q->_items = (int*)malloc(size * sizeof(int)); 
    return q;
}


bool empty(queue *q) { // is the queue empty?
    return q->_elements == 0;
}

void enque(queue* q, int v) {
    if (q->_size == q->_elements){
        int nsize = 2*q->_size;
        int* new = (int*)malloc(nsize*sizeof(int));
        for (int i = 0; i < q->_elements; i++) {
            new[i] = q->_items[(q->_first + i) % q->_size];
        }
        free(q->_items);
        q->_items = new;
        q->_size = nsize;
        q->_first = 0;
        q->_last = q->_elements;
    }
    q->_elements++;
    q->_items[q->_last] = v;
    q->_last = (q->_last + 1) % q->_size;
}
    
int dequeue(queue *q) {
    int res = 0;
    if (q->_elements == 0) {
        printf("Queue is empty.\n");
        return -1;
    }
    q->_elements--;
    int value = q->_items[q->_first];
    q->_first = (q->_first + 1) % q->_size;
    return value;
}

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
    (t_stop->tv_sec - t_start->tv_sec)*1000000000;
}

int *random(int n) {
    int *array = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n ; i++) {
        array[i] = (rand() % (n*10))+1;
    }
    return array;
}

long benchmark(queue *q, int l){
    struct timespec t_start, t_stop;
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    if (l == 0)
        dequeue(q);
    else 
        enque(q, 1);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    return nano_seconds(&t_start, &t_stop);
}


int main()
{
    srand(time(NULL));
    int n = 6;
    for (int i = 1; i < n + 1; i++) {
        int t = 1000;
        int c = 0;
        long *r1 = malloc(sizeof(long) * t);   
        long *r2 = malloc(sizeof(long) * t);   
        int size = (int)pow(10, i);
        
        while (t != 0) {
            int *arr = random(size);
            queue *q = create_queue(size);
            for (int g = 0; g < size; g++) {
                enque(q, arr[g]);
            }
    
            long wall1 = benchmark(q, 0);
            long wall2 = benchmark(q, 1);
    
            r1[c] = wall1;
            r2[c] = wall2;
            c++;
    
            free(arr);
            free(q->_items);
            free(q);
            t--;
        }
    
        long sum1 = 0, sum2 = 0;
        long small1 = LONG_MAX, small2 = LONG_MAX;
        
        for (int j = 0; j < c; j++) {
            sum1 += r1[j]; 
            if (r1[j] < small1) small1 = r1[j];
    
            sum2 += r2[j]; 
            if (r2[j] < small2) small2 = r2[j];
        }
    
        long avg1 = sum1 / c;
        long avg2 = sum2 / c;
    
        printf("%d | dequeue elem (avg %ld ns) (min %ld ns)\n", size, avg1, small1);
        printf("%d | enqueue elem (avg %ld ns) (min %ld ns)\n", size, avg2, small2);
    
        free(r1);
        free(r2);
    }
    return 0;
}