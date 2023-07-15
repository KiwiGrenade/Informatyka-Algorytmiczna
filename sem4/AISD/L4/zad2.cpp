#include <iostream>
#include <cstdio>
#include <zconf.h>
#include "RB_BST.h"

int main(int argc, char* argv[])
{
    char *leftTrace, *rightTrace;
    std::string line;
    std::cin >> line;
    size_t n = std::stoull(line);

    size_t insertList[n],
            deleteList[n];
    // get keys to RB_BST_insert
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
    RB_BST * tree = static_cast<RB_BST *>(malloc(sizeof(RB_BST*)));
    Node * nil = static_cast<Node *>(malloc(sizeof(Node)));
    *nil = (Node){.key = 0,  .left = NULL, .right = NULL, .parent = NULL, .color = BLACK};
    tree->NIL = nil;
    tree->root = tree->NIL;
    for (size_t i : insertList)
    {
        RB_BST_insert(tree, i);
        if( n < 50)
        {
            printf("Insert %lu\n", i);
            RB_BST_print(tree);
            std::cout << std::endl << "Height: " << RB_BST_height(tree) << std::endl;
        }
    }
    for(size_t i : deleteList)
    {
        RB_BST_delete(tree, i);
        if( n < 50)
        {
            printf("Insert %lu\n", i);
            RB_BST_print(tree);
            std::cout << std::endl << "Height: " << RB_BST_height(tree) << std::endl;
        }
    }

    std::cout << "Comparisons: " << comparisions << std::endl;
    std::cout << "Swap or view: " << swapOrView << std::endl;

    RB_BST_clean(tree);
    return 0;
}