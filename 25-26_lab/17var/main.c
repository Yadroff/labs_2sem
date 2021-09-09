#include <stdio.h>
#include <string.h>
#include "deq.h"
#include <limits.h>

#define INF INT_MAX

data procedure(udt *d) {
    data t, a;
    int max = -INF - 1;
    int size = d->size;
    for (int i = 0; i < size; i++) {
        a = udt_top_left(d);
        if (a.key > max) {
            max = udt_top_left(d).key;
            t = udt_top_left(d);
        }
        udt_pop_front(d);
        udt_push_back(d, a);
    }
    udt *d1 = create_udt(NULL);
    while (udt_top_left(d).key != t.key && udt_top_right(d).key != t.key) {
        a = udt_top_left(d);
        udt_push_front(d1, a);
        udt_pop_front(d);
        if (!udt_empty(d)) {
            a = udt_top_right(d);
            udt_push_back(d1, a);
            udt_pop_back(d);
        }
    }
    if (udt_top_left(d).key == t.key) {
        udt_pop_front(d);
    } else {
        udt_pop_back(d);
    }
    while (!udt_empty(d1)){
        udt_push_front(d, udt_top_left(d1));
        udt_pop_front(d1);
    }
    return t;
}

udt* sort(udt *d) {
    int size = udt_size(d);
    udt *d1 = create_udt(NULL);
    data t;
    for (int i = 0; i < size; i++) {
        t = procedure(d);
        udt_push_front(d1, t);
    }
    return d1;
}

int main() {
    int c = 1, ans;
    udt *d = NULL;
    while (c) {
        printf("1. Create deq\t 2. Empty\t 3. Size\t 4. Push back\t 5. Push front\t 6. Top left\t 7. Top right\t 8.Pop back\t 9. Pop front\t 10.Print\t 11. Sort\t 12. Exit\n");
        scanf("%d", &ans);
        switch (ans) {
            case 1: {
                d = create_udt(d);
                break;
            }
            case 2: {
                if (d == NULL) {
                    printf("Deq doesn't exist\n");
                } else {
                    udt_empty(d) ? printf("Deq is empty\n") : printf("Deq isn't empty\n");
                }
                break;
            }
            case 3: {
                if (d == NULL) {
                    printf("Deq doesn't exist\n");
                } else {
                    printf("%d\n", udt_size(d));
                }
                break;
            }
            case 4: {
                if (d == NULL) {
                    printf("Deq doesn't exist\n");
                } else {
                    data tb;
                    printf("Print key\n");
                    scanf("%d", &tb.key);
                    printf("Print string\n");
                    scanf("%s", tb.value);
                    if (!udt_push_back(d, tb)) {
                        printf("Deq is full\n");
                    }
                }
                break;
            }
            case 5: {
                if (d == NULL) {
                    printf("Deq doesn't exist\n");
                } else {
                    data tf;
                    printf("Print key\n");
                    scanf("%d", &tf.key);
                    printf("Print string\n");
                    scanf("%s", tf.value);
                    if (!udt_push_front(d, tf)) {
                        printf("Deq is full\n");
                    }
                }
                break;
            }
            case 6: {
                if (d == NULL) {
                    printf("Deq doesn't exist\n");
                } else {
                    if (udt_empty(d)) {
                        printf("Deq is empty\n");
                    } else {
                        data a = udt_top_left(d);
                        printf("Key\n%d\nValue\n%s\n", a.key, a.value);
                    }
                }
                break;
            }
            case 7: {
                if (d == NULL) {
                    printf("Deq doesn't exist\n");
                } else {
                    if (udt_empty(d)) {
                        printf("Deq is empty\n");
                    } else {
                        data a = udt_top_right(d);
                        printf("Key\n%d\nValue\n%s\n", a.key, a.value);
                    }
                }
                break;
            }
            case 8: {
                if (d == NULL) {
                    printf("Deq doesn't exist\n");
                } else {
                    if (!udt_pop_back(d)) {
                        printf("Deq is empty\n");
                    }
                }
                break;
            }
            case 9: {
                if (d == NULL) {
                    printf("Deq doesn't exist\n");
                } else {
                    if (!udt_pop_front(d)) {
                        printf("Deq is empty\n");
                    }
                }
                break;
            }
            case 10: {
                if (d == NULL) {
                    printf("Deq doesn't exist\n");
                } else {
                    udt_print(d);
                }
                break;
            }
            case 11: {
                if (d == NULL) {
                    printf("Deq doesn't exist\n");
                } else {
                    d = sort(d);
                }
                break;
            }
            case 12: {
                c = 0;
                break;
            }
            default: {
                printf("Wrong answer\n");
            }
        }
    }
    return 0;
}
