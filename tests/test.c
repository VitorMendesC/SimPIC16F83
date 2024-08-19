#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number_elements(void *arr);

int main(int argc, int **argv){
    unsigned const int a = 0b100;
    unsigned const int b = 0b10;

    return 0;
}

int number_elements(void *arr){
    return sizeof(arr)/sizeof(arr[0]) - 1;
}