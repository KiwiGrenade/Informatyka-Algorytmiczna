//
// Created by mango on 05.06.23.
//
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "SplayTree.h"

int main(int argc, char** argv)
{
    std::string line;
    std::cin >> line;
    size_t n = std::stol(line);

    size_t  insertList[n],
            deleteList[n];
    // get keys to RB_BST_insert
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
    Splay_node* root = NULL;
    for(size_t i : insertList)
    {
        root = Splay_insert(root, i);
        if( n < 50)
        {
            printf("Insert %lu\n", i);
            Splay_print(root);
            std::cout << std::endl << "Height: " << Splay_height << std::endl;
        }
    }
    for(size_t i : deleteList)
    {
        root = Splay_delete(root, i);
        if( n < 50)
        {
            printf("Delete %lu\n", i);
            Splay_print(root);
            std::cout << std::endl << "Height: " << Splay_height << std::endl;
        }
    }


    std::cout << "Comparisons: " << comparisions << std::endl;
    std::cout << "Swap or view: " << swapOrView << std::endl;
    
    Splay_clean(root);
    return 0;
}
