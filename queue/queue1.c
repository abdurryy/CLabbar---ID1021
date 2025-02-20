#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

typedef struct node {
    int value;
    struct node *next;
} node;

typedef struct queue {
    node *first;
} queue;

queue *create_queue() {
    queue *q = (queue*)malloc(sizeof(queue));
    q->first = NULL;
    return q;
}

bool empty(queue *q) { // is the queue empty?
    return q->first == NULL;
}

void enque(queue* q, int v) {
    node *nd = (node*)malloc(1*sizeof(node));
    nd->value = v;
    nd->next = NULL;
    node *prv = NULL;
    node *nxt = q->first;
    while (nxt != NULL) {
        prv = nxt;
        nxt = nxt->next;
    }
    if (prv != NULL) {
        prv->next = nd;
    } else {
        q->first = nd;
    }
}
    
int dequeue(queue *q) {
    int res = 0;
    if (q->first != NULL) {
        struct node * nd = q -> first;
        res = nd->value;
        q->first = q->first->next;
        free(nd);
    }
    return res;
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
    for (int i = 1; i < n+1 ; i++) {
        int t = 1;
        int c = 0;
        long *r1 = malloc(sizeof(long) * t);   
        long *r2 = malloc(sizeof(long) * t);   
        int size = (int)pow(10, i);
        while(t!=0){
            int *arr = random(size);
            queue *q = create_queue();
            for (int g = 0; g < size; g++)
            {
                enque(q, arr[g]);
            }
            long wall1 = benchmark(q, 0);
            long wall2 = benchmark(q, 1);
            free(q);
            r1[c] = wall1;
            r2[c] = wall2;
            c++;
            t--;
        }
        long sum = 0;
        long small1 = LONG_MAX;
        for (int i = 0; i < c; i++) {
            sum += r1[i]; 

            if (r1[i] < small1) small1 = r1[i];
        }
        long avg1 = sum / c;
        sum = 0;
        long small2 = LONG_MAX;
        for (int i = 0; i < c; i++) {
            sum += r2[i]; 
            if (r2[i] < small2) small2 = r2[i];
        }
        long avg2 = sum / c;
        printf("%d | dequeue elem (avg %ld ns) (min %ld ns)\n", size, avg1, small1);
        printf("%d | enqueue elem (avg %ld ns) (min %ld ns)\n", size, avg2, small2);
    }
    return 0;
}