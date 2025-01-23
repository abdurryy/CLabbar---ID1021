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
        printf("Stack overflow!\n");
        return;
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
    return stk->array[stk->top];
}

int main() {
    stack *stk = new_stack(4);
    int n = 10;
    for(int i = 0; i < n; i++) {
        push(stk, i+30);
    }
    for(int i = 0; i < stk->top; i++) {
        printf("stack[%d] : %d\n", i, stk->array[i]);
    }
    int val = pop(stk);
    // assuming 0 is returned when the stack is empty
    while(val != 0) { 
        printf("pop : %d\n", val);
        val = pop(stk);
    }
}

