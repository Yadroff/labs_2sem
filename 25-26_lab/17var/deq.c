#include <stdio.h>
#include <malloc.h>
#include "deq.h"

udt *create_udt(udt *d) {
    d = (udt *) malloc(sizeof(udt));
    d->first = d->last = -1;
    d->size = 0;
    return d;
}

bool udt_empty(const udt *d) {
    return d->size == 0;
}

int udt_size(const udt *d) {
    return d->size;
}

bool udt_push_back(udt *d, data t) {
    if (d->size == 10) {
        return false;
    }
    if (!d->size) {
        d->last = d->first = 0;
    } else {
        d->last = (d->last + 1) % 10;
    }
    d->arr[d->last] = t;
    d->size++;
    return true;
}

bool udt_push_front(udt *d, data t) {
    if (d->size == 10) {
        return false;
    }
    if (!d->size) {
        d->first = d->last = 0;
    } else {
        d->first = (10 + (d->first - 1) % 10) % 10;
    }
    d->arr[d->first] = t;
    d->size++;
    return true;
}

bool udt_pop_front(udt *d) {
    if (!d->size) {
        return false;
    }
    if (d->size == 1) {
        d->first = d->last = -1;
        d->size--;
        return true;
    }
    d->first++;
    d->first %= 10;
    d->size--;
    return true;
}

bool udt_pop_back(udt *d) {
    if (!d->size) {
        return false;
    }
    if (d->size == 1) {
        d->first = d->last = -1;
        d->size--;
        return true;
    }
    d->last--;
    d->last = (10 + d->last % 10) % 10;
    d->size--;
    return true;
}

data udt_top_left(udt *d) {
    if (d->size) {
        return d->arr[d->first];
    }
}

data udt_top_right(udt *d) {
    if (d->size) {
        return d->arr[d->last];
    }
}

void udt_print(udt *d) {
    printf("Key\tValue\n");
    int size = udt_size(d);
    for (int i = 0; i < size; i++) {
        data a = udt_top_left(d);
        udt_pop_front(d);
        printf("%d\t", a.key);
        printf("%s\n", a.value);
        udt_push_back(d, a);
    }
}
