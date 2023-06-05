
#ifndef AISD_REDBLACKBSTREE_H
#define AISD_REDBLACKBSTREE_H

#include <stdint.h>
#include <stdlib.h>

typedef struct RedBlackBSTreeNode RB_BST_node;

typedef enum Color{
    RED,
    BLACK
}color_t;

struct RedBlackBSTreeNode{
    uint64_t data;
    RB_BST_node* left;
    RB_BST_node* right;
    RB_BST_node* parent;
    color_t color;
};

typedef struct RB_tree{
    RB_BST_node* root;
    RB_BST_node* NIL;
}RB_tree;

void RB_BSTree_insert(RB_tree* T, uint64_t data);

void RB_BSTree_delete(RB_tree* T, uint64_t key);

size_t RB_BSTree_height(RB_tree* T);

void RB_BSTree_clean(RB_tree* T);

void RedBlackBStree_print(RB_tree* T);

#endif //AISD_REDBLACKBSTREE_H
