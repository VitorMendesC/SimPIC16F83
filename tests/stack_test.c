#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define SIZE_STACK 8
void push(const uint16_t addr);
uint16_t *stack;
uint16_t pop();

int main(int argc, int **argv){
    stack = calloc(SIZE_STACK, 2);
    uint16_t p = 0;

    for(uint16_t i = 1; i < 20; i++){
        push(i);
    }

    for(int j = 0; j < 10; j++){
        p = pop();
    }

    return 0;
}

void push(const uint16_t addr){
    uint8_t stack_full = 1;

    for(int i = 0; i < SIZE_STACK; i++){
        if(stack[i] == 0){
            stack[i] = addr;
            stack_full = 0;
            break;
        }
    }

    if(stack_full){
        for(int j = 1; j < SIZE_STACK; j++){
            stack[j-1] = stack[j];
        }

        stack[SIZE_STACK - 1] = addr; 
    }
}


uint16_t pop(){
    uint16_t addr = 0;

    for(int i = SIZE_STACK - 1; i >= 0; i--){
        if(stack[i] != 0){
            addr = stack[i];
            stack[i] = 0;
            break;
        }
    }

    return addr;
}