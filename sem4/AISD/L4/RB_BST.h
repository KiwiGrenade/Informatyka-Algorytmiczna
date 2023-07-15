
#ifndef AISD_REDBLACKBSTREE_H
#define AISD_REDBLACKBSTREE_H

#include <stdint.h>
#include <stdlib.h>

typedef struct RB_BST_Node Node;

typedef enum Color{
    RED,
    BLACK
}color_t;

struct RB_BST_Node{
    uint64_t key;
    Node* left;
    Node* right;
    Node* parent;
    color_t color;
};

typedef struct RB_BST{
    Node* root;
    Node* NIL;
}RB_tree;

extern size_t comparisions;
extern size_t swapOrView;

void RB_BST_insert(RB_BST* T, size_t data);

void RB_BST_delete(RB_BST* T, size_t key);

size_t RB_BST_height(RB_BST* T);

void RB_BST_clean(RB_BST* T);

void RB_BST_print(RB_BST* T);

#endif //AISD_REDBLACKBSTREE_H
