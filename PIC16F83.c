#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define FREQ (uint64_t)10E6         // Not used
#define SIZE_PROGRAM_MEM 512
#define SIZE_RAM_BYTES 36
#define SIZE_EEPROM_BYTES 64
#define SIZE_STACK 8

#define OP_ADDWF    0b00011100000000
#define OP_CLRF     0b00000110000000
#define OP_CLRW     0b00000100000000
#define OP_DECF     0b00001100000000
#define OP_DECFSZ   0b00001100000000
#define OP_INCF     0b00101000000000
#define OP_INCFSZ   0b00111100000000
#define OP_MOVF     0b00100000000000
#define OP_MOVWF    0b00000010000000
#define OP_SUBWF    0b00001000000000
#define OP_BCF      0b01000000000000
#define OP_BSF      0b01010000000000
#define OP_BTFSC    0b01100000000000
#define OP_BTFSS    0b01110000000000
#define OP_ADDLW    0b11111000000000
#define OP_CALL     0b10000000000000
#define OP_GOTO     0b10100000000000
#define OP_MOVLW    0b11000000000000
#define OP_RETLW    0b11010000000000
#define OP_RETURN   0b00000000001000
#define OP_SLEEP    0b00000001100011
#define OP_SUBLW    0b11110000000000

void decoder(const uint16_t instruct);
void push(const uint16_t addr);
uint16_t pop();

uint16_t *program_counter;
uint16_t *program_mem;
uint16_t *stack;
uint8_t *ram;
uint8_t *eeprom;
uint16_t *reg_instruc;
uint8_t *reg_w;
uint8_t *reg_status;


int main(int argc, char **argv){
    program_mem = calloc(SIZE_PROGRAM_MEM, sizeof(uint16_t));
    stack = calloc(SIZE_STACK, sizeof(uint16_t));
    ram = calloc(SIZE_RAM_BYTES, sizeof(uint8_t));
    eeprom = calloc(SIZE_EEPROM_BYTES, sizeof(uint8_t));

    reg_instruc = calloc(1, sizeof(uint16_t));
    reg_w = calloc(1 , sizeof(uint8_t));
    reg_status = calloc(1 , sizeof(uint8_t));

    FILE *fp_prog_mem;
    FILE *fp_eeprom;

    fp_prog_mem = fopen("program_memory.bin", "rb");
    fread(program_mem, sizeof(uint16_t), SIZE_PROGRAM_MEM, fp_prog_mem);
    fclose(fp_prog_mem);


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