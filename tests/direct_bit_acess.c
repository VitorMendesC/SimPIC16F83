#include <stdlib.h>
#include <stdio.h>

typedef union
{
    struct {
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char reserved:4;
    } bits;
    unsigned char byte;
} HW_RegisterB;


int main(){
    HW_RegisterB reg;

    reg.byte = 0b11111010;

    printf("%d", reg.bits.reserved);

    return 0;
}