#include <stdio.h>
#include <stdlib.h>

struct tnode {
    float value;
    struct tnode *son;
    struct tnode *brother;
    struct tnode *parent;
};
typedef struct tnode node;
typedef struct {
    node *root;
} Tree;


node *create_node(float f, node *par) {
    node *t;
    t = (node *) malloc(sizeof(node));
    t->value = f;
    t->son = NULL;
    t->brother = NULL;
    t->parent = par;
    return t;
}

Tree *create_tree(float f) {
    Tree *t;
    t = (Tree *) malloc(sizeof(Tree));
    t->root = create_node(f, NULL);
    return t;
}


node *search_tree(node *t, float f) {
    if (t == NULL){
        return  t;
    }
    node *tree = NULL;
    if (t->value == f) {
        return t;
    }
    if (t->son != NULL) {
        tree = search_tree(t->son, f);
    }
    if (tree == NULL) {
        tree = search_tree(t->brother, f);
    }
    return tree;
}

void add_node_in_tree(Tree *tree, float par_f, float f) {
    node *t = tree->root;
    t = search_tree(t, par_f);
    if (t == NULL) {
        printf("%-.2f not contains in tree\n", par_f);
        return;
    }
    if (t->son == NULL) {
        t->son = create_node(f, t);
    } else {
        t = t->son;
        while (t->brother != NULL) {
            t = t->brother;
        }
        t->brother = create_node(f, t->parent);
    }
}

void delete_node(Tree *tree, float f) {
    node *t = tree->root;
    t = search_tree(t, f);
    if (t == NULL) {
        printf("%-.2f not contains in tree\n", f);
        return;
    }
    if (t->parent == NULL){
        free(t);
        return;
    }
    if (t->parent->son == t){
        t->parent->son = t->brother;
    }
    else{
        node *tr = t->parent->son;
        while (tr->brother != t){
            tr = tr->brother;
        }
        tr->brother = t->brother;
    }
    free(t);
}

void print_tree(node *t, int x) {
    if (t == NULL) {
        return;
    }
    for (int i = 0; i < x; i++) {
        printf("\t");
    }
    printf("%-.2f\n", t->value);
    print_tree(t->son, x + 1);
    print_tree(t->brother, x);
}

int node_degree(node *t) {
    if (t == NULL || t->son == NULL) {
        return 0;
    }
    int n = 1;
    t = t->son;
    while (t->brother != NULL) {
        t = t->brother;
        n++;
    }
    return n;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int task(node *t, int mx) {
    if (t == NULL || t->son == NULL) {
        return mx;
    }
    int n = node_degree(t);
    mx = max(mx, n);
    mx = max(mx, task(t->son, mx));
    mx = max(mx, task(t->brother, mx));
    return mx;
}

int main() {
    Tree *t = NULL;
    int choose, g = 1;
    while (g) {
        printf("1. Create tree\t 2. Add node to tree\t 3. Delete node from tree\t 4. Task\t 5. Print tree\t 6. Exit \n");
        scanf("%d", &choose);
        switch (choose) {
            case 1: {
                printf("Write tree's root\n");
                float f;
                scanf("%f", &f);
                t = create_tree(f);
                break;
            }
            case 2: {
                printf("Write tree node value\n");
                float f, par_f;
                scanf("%f", &f);
                printf("Write parent value\n");
                scanf("%f", &par_f);
                add_node_in_tree(t, par_f, f);
                break;
            }
            case 3: {
                printf("Write tree node value\n");
                float f;
                scanf("%f", &f);
                delete_node(t, f);
                break;
            }
            case 4: {
                int ans = task(t->root, 0);
                printf("tree grade is %d\n", ans);
                break;
            }
            case 5: {
                print_tree(t->root, 0);
                break;
            }
            case 6: {
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