#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "passenger.h"

void usage() {
    printf("Usage: program [-key] filename\nKeys: -f xor -p\n");
}

int main(int argc, char *argv[]) {
    FILE *in;
    int f = 0, p = 0;
    if (argc != 3) {
        usage();
        return 1;
    }
    if (strcmp(argv[1], "-f") == 0) {
        f = 1;
        in = fopen(argv[2], "r");
    } else if (strcmp(argv[1], "-p") == 0) {
        p = 1;
        in = fopen(argv[2], "r");
    } else {
        usage();
        return 2;
    }
    passenger pas;
    if (!in) {
        perror("Can not open file\n");
        return 3;
    }
    if (f) {
        printf("___________________________________________________________________________________\n");
        printf("|        SURNAME          | I |   N   |   W   |        TO        | TIME | TR | CH |\n");
        printf("___________________________________________________________________________________\n");
    }
    int n = -1;
    int w = INT_MAX;
    while (fread(&pas, sizeof(pas), 1, in) == 1) {
        if (p && pas.num > n) {
            n = pas.num;
        }
        if (f) {
            printf("|%-25s|%-3s|%-7d|%-7d|%-19s|%d:%d|%-4d|%-4d|\n", pas.surname, pas.initials, pas.num, pas.weight,
                   pas.to, pas.time.hour, pas.time.minute, pas.transfer, pas.child);
            printf("___________________________________________________________________________________\n");
        }
    }
    if (f) {
        return 0;
    }
    fseek(in, 0, SEEK_SET);
    while (fread(&pas, sizeof(pas), 1, in) == 1) {
        if (pas.num == n && pas.weight < w) {
            w = pas.weight;
        }
    }
    fseek(in, 0, SEEK_SET);
    if (n == -1) {
        printf("Данные введены неправильно\n");
        return 4;
    }
    printf("\t\t\t\t\tANSWER\n");
    printf("___________________________________________________________________________________\n");
    printf("|        SURNAME          | I |   N   |   W   |        TO        | TIME | TR | CH |\n");
    printf("___________________________________________________________________________________\n");
    while (fread(&pas, sizeof(pas), 1, in) == 1) {
        if (pas.num >= n && pas.weight <= w) {
            printf("|%-25s|%-3s|%-7d|%-7d|%-19s|%d:%d|%-4d|%-4d|\n", pas.surname, pas.initials, pas.num, pas.weight,
                   pas.to, pas.time.hour, pas.time.minute, pas.transfer, pas.child);
            printf("___________________________________________________________________________________\n");
        }
    }
    return 0;
}