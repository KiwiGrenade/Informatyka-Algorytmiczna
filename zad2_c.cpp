#include <iostream>
#include <cstdio>
#include <zconf.h>
#include "RedBlackBSTree.h"

int main(int argc, char* argv[])
{
    char *leftTrace, *rightTrace;
    std::string line;
    std::cin >> line;
    uint64_t n = std::stoull(line);

    uint64_t insertList[n],
            deleteList[n];
    // get keys to insert
    for(uint64_t i = 0; i < n; i++)
    {
        std::cin >> line;
        insertList[i]= std::stoull(line);
    }
    // get keys to delete
    for(uint64_t i = 0; i < n; i++)
    {
        std::cin >> line;
        deleteList[i] = std::stoull(line);
    }
    ////////////////////////////////////////////////////
    RB_tree* tree = static_cast<RB_tree *>(malloc(sizeof(*tree)));
    RB_BST_node* nil = static_cast<RB_BST_node *>(malloc(sizeof(*nil)));
    *nil = (RB_BST_node){.data = 0,  .left = NULL, .right = NULL, .parent = NULL, .color = BLACK};
    tree->NIL = nil;
    tree->root = tree->NIL;
    for (uint64_t number:insertList) {
        RB_BSTree_insert(tree, number);
        printf("Insert %zu\n", number);
        RedBlackBStree_print(tree);
    }
    sleep(1);
    for(uint64_t number : deleteList){
        RB_BSTree_delete(tree, number);
        printf("Delete %zu\n", number);
        RedBlackBStree_print(tree);
    }
    RB_BSTree_clean(tree);
    return 0;
}