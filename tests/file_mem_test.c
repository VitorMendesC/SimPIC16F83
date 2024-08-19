#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate_prog_mem();
void read_prog_mem();

FILE *prog_mem_fp;

int main(int argc, int **argv){
    prog_mem_fp = fopen("program_memory.bin", "wb+");
    generate_prog_mem();
    read_prog_mem();
    

    return 0;
}

void write_prog_mem(const int addr, const int size){
    for(int i = 0; i < size/2; i++){
        fseek(prog_mem_fp, sizeof(int) * addr, SEEK_SET);
        //fwrite(&decoded_data[i], sizeof(int), 1, prog_mem_fp);
    }
    return;
}

void generate_prog_mem(){
    rewind(prog_mem_fp);
    for(int i = 0; i < 512; i++){
        int nop = 0;
        fwrite(&i, sizeof(int), 1, prog_mem_fp);
    }
}

void read_prog_mem(){
    rewind(prog_mem_fp);
    int r;
    for(int i = 0; i < 512; i++){
        fread(&r, sizeof(int), 1, prog_mem_fp);
        printf("%d\n", r);
    }

}
