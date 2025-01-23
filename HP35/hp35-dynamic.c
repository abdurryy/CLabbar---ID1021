#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct stack {
    int top;
    int size;
    int *array;
} stack;

stack *new_stack(int size) {
    int *array = (int*)malloc(size * sizeof(int));
    stack *stk = (stack*)malloc(sizeof(stack));
    stk->array = array;
    stk->top = 0;
    stk->size = size;
    return stk;
}

void push(stack *stk, int val) {
    if (stk->top >= stk->size) {
        int size = stk->size * 2; // jag lägger till 1 plats till
        stk->size = size;
        int *copy = (int*)malloc(size * sizeof(int));
        for (int i = 0; i < stk->top; i++) {
            copy[i] =stk->array[i];
        }
        free(stk->array);
        stk->array = copy;
    }
    stk->array[stk->top] = val;
    stk->top += 1;
}

int pop(stack *stk) {
    if (stk->top <= 0) {
        printf("Stack underflow!\n");
        return 0;
    }

    stk->top -= 1;
    int val = stk->array[stk->top];

    if (stk->top > 0 && stk->top <= stk->size / 4) {
        int size = stk->size / 2;
        stk->size = size;
        int *copy = (int*)malloc(size * sizeof(int));
        for (int i = 0; i < stk->top; i++) {
            copy[i] = stk->array[i];
        }
        free(stk->array);
        stk->array = copy;
    }
    
    return val;
}

int main() {
    int size = 10;
    stack *stk = new_stack(size);
    printf("HP-35 pocket calculator\n");
    
    int n = 100;
    char buff[n];
    char *buffer = buff;
    bool run = true;

    while (run) {
        printf(" > ");
        fgets(buffer, n, stdin);

        if (strcmp(buffer, "\n") == 0) {
            run = false;
        } else if (strcmp(buffer, "+\n") == 0) {
            int b = pop(stk);
            int a = pop(stk);
            push(stk, a + b);
        } else if (strcmp(buffer, "-\n") == 0) {
            int b = pop(stk);
            int a = pop(stk);
            push(stk, a - b);
        } else if (strcmp(buffer, "*\n") == 0) {
            int b = pop(stk);
            int a = pop(stk);
            push(stk, a * b);
        } else {
            int val = atoi(buffer);
            push(stk, val);
        }
    }

    printf("The result is: %d\n\n", pop(stk));
    printf("I love reversed Polish notation, don't you?\n");

    free(stk->array);
    free(stk);
    return 0;
}