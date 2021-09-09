#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "queue.h"

bool udt_procedure(udt *q) {
    if (udt_empty(q)) {
        return false;
    }
    bool ok = false;
    udt *q1 = (udt *) malloc(sizeof(udt)); // очередь из обработанных элементов
    udt_create(q1);
    udt *q2 = (udt *) malloc(sizeof(udt)); // вспомогательная очередь для обмена позициями
    udt_create(q2);
    data cur, prev = udt_top(q);
    while (!udt_empty(q)) {
        cur = udt_top(q);
        udt_pop_front(q);
        if (cur.key < prev.key) {
            ok = true;
            bool ok_1 = false;
            while (!udt_empty(q1)) {
                if (ok_1) {
                    udt_push_back(q2, udt_top(q1));
                    udt_pop_front(q1);
                } else {
                    if (udt_top(q1).key < cur.key) {
                        udt_push_back(q2, udt_top(q1));
                        udt_pop_front(q1);
                    } else {
                        udt_push_back(q2, cur);
                        ok_1 = true;
                    }
                }
            }
            break;
        }
        udt_push_back(q1, cur);
        prev = cur;
    }
    if (ok) { // заканчиваем "перекладывание очереди q в q2"
        while (!udt_empty(q)) {
            udt_push_back(q2, udt_top(q));
            udt_pop_front(q);
        }
        q1 = q2;
    }
    udt_create(q); // очистим буфер очереди
    while (!udt_empty(q1)) { // возвращение элементов в очередь
        data a = udt_top(q1);
        udt_push_back(q, a);
        udt_pop_front(q1);
    }
    return ok;
}

void udt_sort(udt *q) {
    while (udt_procedure(q)) {}
}

int main() {
    int c = 1, ans;
    udt *q = (udt *) malloc(sizeof(udt));
    while (c) {
        printf("1. Create queue\t 2. Empty\t 3. Size\t 4. Push back\t 5. Top\t 6.Pop\t 7.Print\t 8. Sort\t 9. Exit\n");
        scanf("%d", &ans);
        switch (ans) {
            case 1: {
                udt_create(q);
                break;
            }
            case 2: {
                udt_empty(q) ? printf("Queue is empty\n") : printf("Queue isn't empty\n");
                break;
            }
            case 3: {
                printf("%d\n", udt_size(q));
                break;
            }
            case 4: {
                data t;
                char a[40];
                printf("Print key\n");
                scanf("%d", &t.key);
                printf("Print string\n");
                scanf("%s", a);
                strcpy(t.value, a);
                if (!udt_push_back(q, t)) {
                    printf("Queue is full\n");
                }
                break;
            }
            case 5: {
                if (udt_empty(q)) {
                    printf("Queue is empty\n");
                } else {
                    data a = udt_top(q);
                    printf("Key\n%d\nValue\n%s\n", a.key, a.value);
                }
                break;
            }
            case 6: {
                if (!udt_pop_front(q)) {
                    printf("Queue is empty\n");
                }
                break;
            }
            case 7: {
                udt_print(q);
                break;
            }
            case 8: {
                udt_sort(q);
                break;
            }
            case 9: {
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