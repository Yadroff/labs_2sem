#ifndef _UDT_H_
#define _UDT_H_

#include <stdbool.h>
typedef struct {
    int key;
    char value[40];
} data;

typedef struct {
    int first;
    int size;
    data arr[10];
} udt;

void udt_create(udt *);

bool udt_empty(const udt *);

bool udt_push_back(udt *, data);

bool udt_pop_front(udt *);

data udt_top(udt *);

void udt_print(udt *);

int udt_size(const udt *);

#endif