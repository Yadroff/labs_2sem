#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Item {
    struct Item *next;
    float data;
};

typedef struct {
    struct Item *node;
} Iterator;

bool Equal(Iterator *lhs, Iterator *rhs) {
    return lhs->node == rhs->node;
}

Iterator *Next(Iterator *i) {
    i->node = i->node->next;
    return i;
}

float Fetch(const Iterator *i) {
    return i->node->data;
}

void Store(const Iterator *i, const float t) {
    i->node->data = t;
}

typedef struct {
    struct Item *head;
    int size;
} List;

void Create(List *l) {
    l->head = malloc(sizeof(struct Item));
    l->head->next = l->head;
    l->size = 0;
}

Iterator First(const List *l) {
    Iterator res = {l->head->next};
    return res;
}

Iterator Last(const List *l) {
    Iterator res = {l->head};
    return res;
}

bool Empty(const List *l) {
    Iterator fst = First(l);
    Iterator lst = Last(l);
    return Equal(&fst, &lst);
}

Iterator Insert(List *l, Iterator *i, const float t) {
    Iterator res = {malloc(sizeof(struct Item))};
    if (!res.node) {
        return Last(l);
    }
    res.node->data = t;
    res.node->next = i->node->next;
    i->node->next = res.node;
    l->size++;
    return res;
}

Iterator Delete(List *l, Iterator *i) {
    Iterator res = Last(l);
    Iterator next = {i->node->next};
    if (Equal(&res, &next)) {
        return res;
    }
    res.node = i->node->next->next;
    struct Item *a = i->node->next;
    i->node->next = res.node;
    free(a);
    l->size--;
    return res;
}

int Size(const List *l) {
    return l->size;
}

void print_list(const List *l) {
    if (l->head == NULL) {
        printf("List doesn't exists\n");
        return;
    }
    Iterator lst = Last(l);
    for (Iterator i = First(l); !Equal(&i, &lst); Next(&i)) {
        printf("%.4f ", Fetch(&i));
    }
    printf("\n");
}

void task(List *l) {
    Iterator lst = Last(l);
    for (Iterator i = First(l); !Equal(&i, &lst); Next(&i), Next(&i)) {
        if (i.node->next == lst.node) {
            return;
        }
        float c = i.node->data;
        Iterator j = {i.node->next};
        Store(&i, Fetch(&j));
        Store(&j, c);
    }
}

Iterator search_prev(const List *l, const int n) {
    Iterator res = Last(l);
    for (int i = 0; i <= n - 1; i++) {
        Next(&res);
    }
    return res;
}

void Destroy(List *l) {
    struct Item *i = l->head->next;
    while (i != l->head) {
        struct Item *pi = i;
        i = i->next;
        free(pi);
    }
    free(l->head);
    l->head = 0;
    l->size = 0;
}

int main() {
    List *l = malloc(sizeof(List));
    Create(l);
    int num = 0;
    int choose;
    bool g = true;
    while (g) {
        printf("1. Print list\t 2. Insert in list\t 3. Delete from list\t 4. Size\t 5. Task\t 6. Exit\n");
        scanf("%d", &choose);
        switch (choose) {
            case 1: {
                print_list(l);
                break;
            }
            case 2: {
                if (l->head == NULL) {
                    Create(l);
                }
                Iterator i = Last(l);
                float val;
                printf("Write value\n");
                scanf("%f", &val);
                if (l->size != 0) {
                    printf("Write the number where you want insert element\n");
                    scanf("%d", &num);
                    if (0 <= num && num <= Size(l)) {
                        i = search_prev(l, num);
                    } else {
                        printf("Element with %d number doesn't exists\n", num);
                        break;
                    }
                }
                Insert(l, &i, val);
                break;
            }
            case 3: {
                if (l->head == NULL) {
                    printf("List doesn't exists\n");
                    break;
                }
                float prev;
                printf("Write number of deleted element\n");
                scanf("%d", &num);
                if (num == Size(l)) {
                    Destroy(l);
                    break;
                }
                if (0 <= num && num < Size(l)) {
                    Iterator i = search_prev(l, num);
                    Delete(l, &i);
                } else {
                    printf("Element with %d number doesn't exists\n", num);
                }
                break;
            }
            case 4: {
                if (l->head == NULL) {
                    printf("List doesn't exists\n");
                    break;
                }
                printf("%d\n", Size(l));
                break;
            }
            case 5: {
                if (l->head == NULL) {
                    printf("List doesn't exists\n");
                    break;
                }
                if (Size(l) != 1) {
                    task(l);
                }
                break;
            }
            case 6: {
                g = false;
                break;
            }
            default: {
                printf("Wrong answer\n");
            }
        }
    }
    return 0;
}
