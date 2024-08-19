#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFF_SIZE 60
#define SUBBUFF_SIZE 60
#define SIZE_PROGRAM_MEM 512

int read_record();
void decode_data(const int size);
void generate_prog_mem();
void write_prog_mem(const int addr, const int size);

FILE *hex_fp;
FILE *prog_mem_fp;
char data[BUFF_SIZE];
uint16_t decoded_data[30] = {0};

int main(int argc, char **argv){
    int return_code;
    hex_fp = fopen(argv[1], "r");
    prog_mem_fp = fopen("program_memory.bin", "wb");

    if(argc != 2){
        printf("USAGE: programmer hex_file.hex");
        return 1;
    }

    if(hex_fp == NULL){
        printf("Error opening HEX file.");
        return 2;
    }
    if(prog_mem_fp == NULL){
        printf("Error opening program memory file.");
        return 3;
    }

    generate_prog_mem();

    do{
        return_code = read_record();
    } while (return_code != 1);
    
    fclose(hex_fp);
    fclose(prog_mem_fp);

    return 0;
}


int read_record(){
    /* Returns 1 EOF, 0 otherwise */
    int ind;
    char buffer[BUFF_SIZE];
    char subbuff[SUBBUFF_SIZE];
    int num_bytes, addr, type, checksum;

    fgets(buffer, BUFF_SIZE, hex_fp);

    // it's highly likely that there is a better way to do this,
    // unfortunately, I don't know it.
    ind = 1;
    memcpy(subbuff, buffer + ind, 2);
    subbuff[2] = '\0';
    num_bytes = (int)strtol(subbuff, NULL, 16);

    ind += 2;
    memcpy(subbuff, buffer + ind, 4);
    subbuff[4] = '\0';
    addr = (int)strtol(subbuff, NULL, 16);
    addr = (int)addr/2;

    ind += 4;
    memcpy(subbuff, buffer + ind, 2);
    subbuff[2] = '\0';
    type = (int)strtol(subbuff, NULL, 16);

    ind += 2;
    memcpy(data, buffer + ind, 2*num_bytes);
    data[2*num_bytes] = '\0';

    ind += 2*num_bytes;
    memcpy(subbuff, buffer + ind, 2);
    subbuff[2] = '\0';
    checksum = (int)strtol(subbuff, NULL, 16);

    if(type == 0){
        decode_data(num_bytes);
        write_prog_mem(addr,num_bytes);
        return 0;
    }
    else if (type == 1){
        return 1;
    }
}

void decode_data(const int size){
    char hex[5];
    int j = 0;

    for(int i = 0; i < size; i+= 2){
        memcpy(hex+2, &data[i], 2);
        memcpy(hex, &data[i+2], 2);

        decoded_data[j] = (uint16_t)strtol(hex, NULL, 16);
        j++;
    }

    return;
}

void generate_prog_mem(){
    rewind(prog_mem_fp);
    for(int i = 0; i < SIZE_PROGRAM_MEM; i++){
        int nop = 0;
        fwrite(&nop, sizeof(uint16_t), 1, prog_mem_fp);
    }
}

void write_prog_mem(const int addr, const int size){
    int fs_ret, fw_ret;

    fs_ret = fseek(prog_mem_fp, sizeof(uint16_t) * addr, SEEK_SET);
    if(fs_ret){
        printf("Error on address seeking");
    }

    for(int i = 0; i < size/2; i++){
        fw_ret = fwrite(&decoded_data[i], sizeof(uint16_t), 1, prog_mem_fp);
        if (!fw_ret){
            printf("Error on writing");
        }
        
    }
    return;
}

