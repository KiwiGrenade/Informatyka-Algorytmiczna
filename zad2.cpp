#include <iostream>
#include <cstdio>
#include <zconf.h>
#include "RB_BSTree.h"

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
    RBTree * tree = static_cast<RBTree *>(malloc(sizeof(RBTree*)));
    Node * nil = static_cast<Node *>(malloc(sizeof(Node)));
    *nil = (Node){.key = 0,  .left = NULL, .right = NULL, .parent = NULL, .color = BLACK};
    tree->NIL = nil;
    tree->root = tree->NIL;
    for (size_t i : insertList)
    {
        insert(tree, i);
        if( n < 50)
        {
            printf("Insert %lu\n", i);
            print(tree);
        }
        size_t h = height(tree);
//        printf("Height: %lu", h);
//        printf("\n\n");
    }
    sleep(1);
    for(size_t i : deleteList)
    {
        nodeDelete(tree, i);
        if( n < 50)
        {
            printf("Insert %lu\n", i);
            print(tree);
        }
        size_t h = height(tree);
//        printf("Height: %lu", h);
//        printf("\n\n");
    }

    std::cout << "Comparisons: " << comparisions << std::endl;
    std::cout << "Swap or view: " << swapOrView << std::endl;

    BSClean(tree);
    return 0;
}