#include <iostream>
#include "BinarySearchTree.h"
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

    BSTree_node* root = NULL;

    for(size_t i : insertList)
    {
        root = BST_insert(root, i);
        if( n < 50)
        {
            std::cout << "Insert: " << i << std::endl;
            std::cout << "Tree: " << std::endl;
            BSTprint(root);
            printf("\n\n");
        }
        std::cout << "Height: " << BST_height(root) << std::endl;
    }
    for(size_t i : deleteList)
    {
        root = BST_delete(root, i);
        if( n < 50)
        {
            std::cout << "Delete: " << i << std::endl;
            std::cout << "Tree: " << std::endl;
            BSTprint(root);
            printf("\n\n");
        }
        std::cout << "Height: " << BST_height(root) << std::endl;
    }

    std::cout << std::endl << "Comparisons: " << comparisions << std::endl;
    std::cout << std::endl << "Swaps or views: " << swapOrView << std::endl;

    BSTree_clean(root);

    return 0;
}
