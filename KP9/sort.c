#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING_SIZE 100
#define MAX_TEXT_SIZE 100
typedef struct {
    int data;
    char value[4];
} key;

typedef struct {
    key k;
    char str[MAX_STRING_SIZE];
} line;

line l[MAX_TEXT_SIZE];
int n = 0;

void print_table() {
    printf("Key\t String\n");
    for (int i = 0; i < n; i++) {
        printf("%c%c%c%c %d\t %s", l[i].k.value[0], l[i].k.value[1], l[i].k.value[2], l[i].k.value[3], l[i].k.data,
               l[i].str);
    }
}

int strless(char a[4], char b[4]) {
    for (int i = 0; i < 4; i++) {
        if (a[i] < b[i]) {
            return -1;
        }
        if (a[i] == b[i]) {
            continue;
        }
        return 1;
    }
    return 0;
}

bool key_equal(key a, key b) {
    return (strless(a.value, b.value) == 0) && (a.data == b.data);
}

bool operator_less(key a, key b) {
    int ans = strless(a.value, b.value);
    if (ans == 0) {
        return a.data < b.data;
    } else {
        return ans < 0;
    }
}

void shaker_sort() {
    int left = 0, right = n - 1;
    int flag = 1;
    while ((left < right) && flag) {
        flag = 0;
        for (int i = left; i < right; i++) {
            if (operator_less(l[i + 1].k, l[i].k)) {
                line tmp = l[i];
                l[i] = l[i + 1];
                l[i + 1] = tmp;
                flag = 1;
            }
        }
        right--;
        for (int i = right; i > left; i--) {
            if (!operator_less(l[i - 1].k, l[i].k)) {
                line tmp = l[i];
                l[i] = l[i - 1];
                l[i - 1] = tmp;
                flag = 1;
            }
        }
        left++;
    }
}

void reverse() {
    for (int i = 0; i < n / 2; i++) {
        line t = l[i];
        l[i] = l[n - 1 - i];
        l[n - 1 - i] = t;
    }
}

void random_table() {
    for (int i = 0; i < n; i++) {
        int j = random() % n;
        line t = l[i];
        l[i] = l[j];
        l[j] = t;
    }
}

void binary_search(key k) {
    int left = 0, right = n, m;
    while (left <= right) {
        m = (left + right) / 2;
        if (key_equal(k, l[m].k)) {
            left = m;
            break;
        }
        if (operator_less(l[m].k, k)) {
            left = m - 1;
        } else {
            right = m + 1;
        }
    }
    if (key_equal(l[left].k, k)) {
        printf("%c%c%c%c %d\t %s", l[left].k.value[0], l[left].k.value[1], l[left].k.value[2], l[left].k.value[3],
               l[left].k.data,
               l[left].str);
    } else {
        printf("Key not found\n");
    }
}

int main(int argc, char *argv[]) {
    key k1, k2;
    FILE *f;
    if (argc != 2) {
        printf("Use: program_name input_file\n");
        return 0;
    }
    if ((f = fopen(argv[1], "r")) == NULL) {
        printf("Can not open file\n");
        return 0;
    }
    while (!feof(f)) {
        fscanf(f, "%s\t%d\t", l[n].k.value, &l[n].k.data);
        fgets(l[n].str, MAX_STRING_SIZE, f);
        n++;
    }
    n--;
    int ans, c = 1;
    while (c) {
        printf("1. Print table\t 2. Shaker sort\t 3. Random\t 4. Reverse \t 5. Binary search \t 6. Exit\n");
        scanf("%d", &ans);
        switch (ans) {
            case 1: {
                print_table();
                break;
            }
            case 2: {
                printf("Before:\n");
                print_table();
                shaker_sort();
                printf("After:\n");
                print_table();
                break;
            }
            case 3: {
                random_table();
                break;
            }
            case 4: {
                reverse();
                break;
            }
            case 5: {
                key k;
                printf("Enter key: ");
                scanf("%s %d", k.value, &k.data);
                binary_search(k);
                break;
            }
            case 6: {
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
