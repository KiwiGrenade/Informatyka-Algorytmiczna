
#ifndef AISD_BINARYSEARCHTREE_H
#define AISD_BINARYSEARCHTREE_H

#include <stdint.h>

typedef struct BinarySearchTreeNode BSTree_node;

struct BinarySearchTreeNode{
    uint64_t key;
    BSTree_node* left;
    BSTree_node* right;
};

extern long long comparisions;
extern long long swapOrView;

BSTree_node* BST_insert(BSTree_node* root, uint64_t val);

BSTree_node* BST_delete(BSTree_node* root, uint64_t key);

size_t BST_height(BSTree_node* root);

void BST_clean(BSTree_node* root);

void BST_print(BSTree_node * root);


#endif //AISD_BINARYSEARCHTREE_H
