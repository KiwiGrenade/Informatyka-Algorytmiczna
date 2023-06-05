
#ifndef AISD_REDBLACKBSTREE_H
#define AISD_REDBLACKBSTREE_H

#include <stdint.h>
#include <stdlib.h>

typedef struct RedBlackBSTreeNode Node;

typedef enum Color{
    RED,
    BLACK
}color_t;

struct RedBlackBSTreeNode{
    uint64_t key;
    Node* left;
    Node* right;
    Node* parent;
    color_t color;
};

typedef struct RBTree{
    Node* root;
    Node* NIL;
}RB_tree;

int comparisions = 0;
int swapOrView = 0;

void insert(RBTree* T, size_t data);

void nodeDelete(RBTree* T, size_t key);

size_t height(RBTree* T);

void BSClean(RBTree* T);

void print(RBTree* T);

#endif //AISD_REDBLACKBSTREE_H
