//
// Created by mango on 04.06.23.
//
#include <iostream>
#include "RB_BST.h"
int main(int argc, char* argv[])
{
    char *leftTrace, *rightTrace;
    std::string line;
    std::cin >> line;
    size_t n = std::stol(line);

    size_t  insertList[n],
            deleteList[n];
    // get keys to insert
    for(size_t i = 0; i < n; i++)
    {
        std::cin >> line;
        insertList[i]= std::stol(line);
    }
    // get keys to delete
    for(size_t i = 0; i < n; i++)
    {
        std::cin >> line;
        deleteList[i] = std::stol(line);
    }

    leftTrace = (char*) malloc(n * sizeof (char));
    rightTrace = (char*) malloc(n * sizeof (char));
    RB_BST* tree = new RB_BST();
    for(size_t i : insertList)
    {
        tree->insert(i);
        if( n < 50)
        {
            std::cout << "Insert: " << i << std::endl;
            std::cout << "Tree: " << std::endl;
            tree->print(tree->root, 0, '-', leftTrace, rightTrace);
            printf("\n\n");
        }
    }
    for(size_t i : deleteList)
    {
        tree->deleteFirstOf(i);
        if( n < 50)
        {
            std::cout << "Delete: " << i << std::endl;
            std::cout << "Tree: " << std::endl;
            tree->print(tree->root, 0, '-', leftTrace, rightTrace);
            printf("\n\n");
        }
    }
    free(leftTrace);
    free(rightTrace);
    free(tree);
    return 0;
}
