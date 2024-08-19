#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SIZE_PROGRAM_MEM 512

int main(int argc, char **argv){

    FILE *fp = fopen("program_memory.bin", "rb");
    uint16_t data;

    printf("Address: value");
    for(int i = 0; i < SIZE_PROGRAM_MEM; i++){
        fread(&data, sizeof(uint16_t), 1, fp);
        printf("\n%6d: %6X", i, data);
    }

    return 0;
}