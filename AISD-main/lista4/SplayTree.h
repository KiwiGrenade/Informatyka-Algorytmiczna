
#ifndef AISD_SPLAYTREE_H
#define AISD_SPLAYTREE_H

#include <stdint.h>

typedef struct SplayNode Splay_node;

struct SplayNode{
    uint64_t data;
    Splay_node* left;
    Splay_node* right;
};

Splay_node* Splay_insert(Splay_node* root, uint64_t data);

Splay_node* Splay_delete(Splay_node* root, uint64_t data);

Splay_node* Splay_search(Splay_node* root, uint64_t data);

void Splay_print(Splay_node* root);

size_t Splay_height(Splay_node* root);

void Splay_clean(Splay_node* root);

#endif //AISD_SPLAYTREE_H
