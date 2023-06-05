
#ifndef AISD_BINARYSEARCHTREE_H
#define AISD_BINARYSEARCHTREE_H

#include <stdint.h>

typedef struct BinarySearchTreeNode BSTree_node;

struct BinarySearchTreeNode{
    uint64_t data;
    BSTree_node* left;
    BSTree_node* right;
};

BSTree_node* BSTree_insert(BSTree_node* root, uint64_t data);

BSTree_node* BSTree_delete(BSTree_node* root, uint64_t key);

size_t BSTree_height(BSTree_node* root);

void BSTree_clean(BSTree_node* root);

void BStree_print(BSTree_node * root);


#endif //AISD_BINARYSEARCHTREE_H
