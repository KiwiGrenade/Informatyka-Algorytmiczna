#include <iostream>
#include <cstdio>
#include <zconf.h>
#include "RedBlackBSTree.h"
int main(int argc, char* argv[])
{
    char *leftTrace, *rightTrace;
    std::string line;
    std::cin >> line;
    size_t n = std::stoull(line);

    size_t insertList[n],
            deleteList[n];
    // get keys to insert
    for(size_t i = 0; i < n; i++)
    {
        std::cin >> line;
        insertList[i]= std::stoull(line);
    }
    // get keys to delete
    for(size_t i = 0; i < n; i++)
    {
        std::cin >> line;
        deleteList[i] = std::stoull(line);
    }
    ////////////////////////////////////////////////////
    auto tree = static_cast<RB_tree *>(malloc(sizeof(RB_tree*)));
    auto nil = static_cast<RB_BST_node *>(malloc(sizeof(RB_BST_node*)));
    *nil = (RB_BST_node){.data = 0,  .left = NULL, .right = NULL, .parent = NULL, .color = BLACK};
    tree->NIL = nil;
    tree->root = tree->NIL;
    for (size_t i = 0; i < n; i++)
    {
        RB_BSTree_insert(tree, insertList[i]);
        printf("Insert %zu\n", insertList[i]);
        RedBlackBStree_print(tree);
    }
    sleep(1);
    for(size_t number : deleteList){
        RB_BSTree_delete(tree, number);
        printf("Delete %zu\n", number);
        RedBlackBStree_print(tree);
    }
    RB_BSTree_clean(tree);
    return 0;
}