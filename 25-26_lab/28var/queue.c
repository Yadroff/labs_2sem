#include <stdio.h>
#include "queue.h"

void udt_create(udt *q) {
    q->first = q->size = 0;
}

bool udt_empty(const udt *q) {
    return q->size == 0;
}

int udt_size(const udt *q) {
    return q->size;
}

bool udt_push_back(udt *q, data t) {
    if (q->size == 10) {
        return false;
    }
    q->arr[(q->first + q->size++) % 10] = t;
    return true;
}

bool udt_pop_front(udt *q) {
    if (!q->size) {
        return false;
    }
    q->first++;
    q->first %= 10;
    q->size--;
    return true;
}

data udt_top(udt *q) {
    if (q->size) {
        return q->arr[q->first];
    }
}

void udt_print(udt *q) {
    printf("Key\tValue\n");
    int size = udt_size(q);
    for (int i = 0; i < size; i++) {
        data a = udt_top(q);
        udt_pop_front(q);
        printf("%d\t", a.key);
        printf("%s\n", a.value);
        udt_push_back(q, a);
    }
}