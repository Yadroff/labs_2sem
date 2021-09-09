#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "passenger.h"

void usage(){
    printf("Usage: program input_filename output_filename\n");
}

int readpassenger(FILE *in, passenger *p){
    return fscanf(in, "%[^\t]\t%[^\t]\t%d\t%d\t%[^\t]\t%d:%d\t%d\t%d\n", p->surname, p->initials, &p->num, &p->weight, p->to, &p->time.hour, &p->time.minute, &p->transfer, &p->child) == 9;
}

int main(int argc, char* argv[]){
    if (argc != 3){
        usage();
        return 1;
    }
    passenger p;
    FILE *out = fopen(argv[2], "w");
    FILE *in = fopen(argv[1], "r");
    if (!(out&&in)){
        perror("Can't open file");
        return 2;
    }
    while (readpassenger(in, &p)){
        fwrite(&p, sizeof (p), 1, out);
    }
    return 0;
}