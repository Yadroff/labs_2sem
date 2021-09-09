#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode {
    char data[40];
    struct tnode *left, *right;
};
typedef struct tnode *node;

int op(char data[40]) {
    if (data[0] == '^' || data[0] == '/' || data[0] == '*' || data[0] == '+' || data[0] == '-') {
        return 1;
    }
    return 0;
}

int priority(char c) {
    switch (c) {
        case '-' :
        case '+' :
            return 1;
        case '*' :
        case '/' :
            return 2;
        case '^' :
            return 3;
        default:
            return 100;
    }
}

node MakeTree(char Expr[], int first, int last) {
    int MinPrt, k, prt, nest = 0;
    node Tree = (node) malloc(sizeof(node));
    MinPrt = 100;
    for (int i = first; i <= last; i++) {
        if (Expr[i] == '(') {
            nest++;
            continue;
        }
        if (Expr[i] == ')') {
            nest--;
            continue;
        }
        if (nest > 0) {
            continue;
        }
        prt = priority(Expr[i]);
        if (prt <= MinPrt) {
            MinPrt = prt;
            k = i;
        }
    }
    if (nest != 0) {
        printf("Wrong expression\n");
        exit(1);
    }
    if (MinPrt == 100) {
        if (Expr[first] == '(' && Expr[last] == ')') {
            free(Tree);
            return MakeTree(Expr, first + 1, last - 1);
        } else {
            k = last - first + 1;
            for (int i = 0; i < k; i++) {
                Tree->data[i] = Expr[first + i];
            }
            Tree->data[k] = '\n';
            Tree->left = NULL;
            Tree->right = NULL;
            return Tree;
        }
    }
    Tree->data[0] = Expr[k];
    Tree->data[1] = '\n';
    Tree->left = MakeTree(Expr, first, k - 1);
    Tree->right = MakeTree(Expr, k + 1, last);
    return Tree;
}

node parent(node t, node son) {
    if (t == NULL) {
        return NULL;
    }
    if (t->left == son || t->right == son) {
        return t;
    }
    node left = parent(t->left, son);
    node right = parent(t->right, son);
    return (left == NULL) ? right : left;
}

void print_tree(node t, int x) {
    if (t == NULL) {
        return;
    }
    print_tree(t->right, x + 1);
    for (int i = 0; i < x; i++) {
        printf("\t");
    }
    for (int i = 0; i <= 40; i++) {
        if (t->data[i] != '\n') {
            printf("%c", t->data[i]);
            continue;
        }
        printf("\n");
        break;
    }
    print_tree(t->left, x + 1);
}

void print_expression(node t) {
    if (t == NULL) {
        return;
    }
    if (op(t->data) && op(t->left->data) &&
        (priority(t->left->data[0]) < priority(t->data[0]) || t->left->data[0] == '^' && t->data[0] == '^')) {
        printf("(");
        print_expression(t->left);
        printf(")");
    } else {
        print_expression(t->left);
    }
    for (int i = 0; i <= 40; i++) {
        if (t->data[i] != '\n') {
            printf("%c", t->data[i]);
            continue;
        }
        break;
    }
    if (op(t->data) && op(t->right->data) &&
        (priority(t->right->data[0]) < priority(t->data[0]) || t->right->data[0] == '^' && t->data[0] == '^')) {
        printf("(");
        print_expression(t->right);
        printf(")");
    } else {
        print_expression(t->right);
    }
}

void transform(node T, node t) {
    if (t == NULL) {
        return;
    }
    if (t->data[0] == '^' && t->right->data[0] == '2' && t->right->data[1] == '\n' && t->left->data[0] == '+') {
        node a = t->left->left;
        node b = t->left->right;
        t->left = (node) malloc(sizeof(node));
        t->right = (node) malloc(sizeof(node));
        t->data[0] = '+';
        t->right->data[0] = '^';
        t->right->data[1] = '\n';
        t->right->left = b;
        t->right->right = (node) malloc(sizeof(node));
        t->right->right->data[0] = '2';
        t->right->right->data[1] = '\n';
        t->left->data[0] = '+';
        t->left->data[1] = '\n';
        t->left->left = (node) malloc(sizeof(node));
        t->left->left->data[0] = '^';
        t->left->left->data[1] = '\n';
        t->left->left->left = a;
        t->left->left->right = (node) malloc(sizeof(node));
        t->left->left->right->data[0] = '2';
        t->left->left->right->data[1] = '\n';
        t->left->right = (node) malloc(sizeof(node));
        t->left->right->data[0] = '*';
        t->left->right->data[1] = '\n';
        t->left->right->left = (node) malloc(sizeof(node));
        t->left->right->right = b;
        t->left->right->left->data[0] = '*';
        t->left->right->left->data[1] = '\n';
        t->left->right->left->left = (node) malloc(sizeof(node));
        t->left->right->left->left->data[0] = '2';
        t->left->right->left->left->data[1] = '\n';
        t->left->right->left->right = a;
        t->left->left->right->left = NULL;
        t->left->left->right->right = NULL;
        t->right->right->left = NULL;
        t->right->right->right = NULL;
        t->left->right->left->left->left = NULL;
        t->left->right->left->left->right = NULL;
        transform(T, parent(T, t));
    }
    transform(T, t->left);
    transform(T, t->right);
}

int main() {
    node t = NULL;
    int choose, g = 1;
    while (g) {
        printf("1. Create tree\t 2. Transform expression\t 3. Print tree\t 4. Print expression\t 5.Exit\n");
        scanf("%d", &choose);
        switch (choose) {
            case 1: {
                printf("Input your expression\n");
                char Expr[1000];
                scanf("%s", Expr);
                int n = 0;
                while (Expr[n] != '\0') {
                    n++;
                }
                t = MakeTree(Expr, 0, n - 1);
                parent(t, NULL);
                break;
            }
            case 2: {
                transform(t, t);
                break;
            }
            case 3: {
                print_tree(t, 0);
                break;
            }
            case 4: {
                print_expression(t);
                printf("\n");
                break;
            }
            case 5: {
                g = 0;
                break;
            }
            default: {
                printf("Wrong answer\n");
            }
        }
    }
    return 0;
}