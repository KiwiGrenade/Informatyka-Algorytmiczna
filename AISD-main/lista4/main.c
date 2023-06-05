#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "mtwister-master/mtwister.h"
#include "BinarySearchTree.h"
#include "RedBlackBSTree.h"
#include "SplayTree.h"


int main(int argc, char** argv)
{
    MTRand r = seedRand((unsigned long) time(NULL));
    if(argc < 2){
        printf("Podano za mało parametrów \n");
        return 1;
    }
    if(strcmp(argv[1], "binary")==0){
        printf("[Dodawanie rosnącego ciągu kluczy]\n");
        sleep(1);
        BSTree_node* root = NULL;
        for (uint64_t i = 1; i <= 50; ++i) {
            root = BSTree_insert(root, i);
            printf("Insert %lu\n", i);
            BStree_print(root);
        }
        printf("[Usuwanie losowego ciągu kluczy]\n");
        sleep(1);
        for(size_t i = 0; i<50; i++){
            uint64_t td = genRandLong(&r)%50 + 1;
            root = BSTree_delete(root, td);
            printf("Delete %lu\n", td);
            BStree_print(root);
        }
        BSTree_clean(root);
        printf("[Dodawanie losowego ciągu kluczy]\n");
        sleep(1);
        root = NULL;
        for (uint64_t i = 1; i <= 50; ++i) {
            uint64_t td = genRandLong(&r)%50 + 1;
            root = BSTree_insert(root, td);
            printf("Insert %lu\n", td);
            BStree_print(root);
        }
        printf("[Usuwanie losowego ciągu kluczy]\n");
        sleep(1);
        for(size_t i = 0; i<50; i++){
            uint64_t td = genRandLong(&r)%50 + 1;
            root = BSTree_delete(root, td);
            printf("Delete %lu\n", td);
            BStree_print(root);
        }
        BSTree_clean(root);
    }
    else if(strcmp(argv[1], "redblack")==0){
        printf("[Dodawanie rosnącego ciągu kluczy]\n");
        sleep(1);
        RB_tree* tree = malloc(sizeof(*tree));
        RB_BST_node* nil = malloc(sizeof(*nil));
        *nil = (RB_BST_node){.color = BLACK, .data =0 , .parent = NULL, .right = NULL, .left = NULL};
        tree->NIL = nil;
        tree->root = tree->NIL;
        for (uint64_t i = 1; i <= 50; ++i) {
            RB_BSTree_insert(tree, i);
            printf("Insert %lu\n", i);
            RedBlackBStree_print(tree);
        }
        printf("[Usuwanie losowego ciągu kluczy]\n");
        sleep(1);
        for(size_t i = 0; i<50; i++){
            uint64_t td = genRandLong(&r)%50 + 1;
            RB_BSTree_delete(tree, td);
            printf("Delete %lu\n", td);
            RedBlackBStree_print(tree);
        }
        RB_BSTree_clean(tree);
        printf("[Dodawanie losowego ciągu kluczy]\n");
        sleep(1);
        tree = malloc(sizeof(*tree));
        nil = malloc(sizeof(*nil));
        *nil = (RB_BST_node){.color = BLACK, .data =0 , .parent = NULL, .right = NULL, .left = NULL};
        tree->NIL = nil;
        tree->root = tree->NIL;
        for (uint64_t i = 1; i <= 50; ++i) {
            uint64_t td = genRandLong(&r)%50 + 1;
            RB_BSTree_insert(tree, td);
            printf("Insert %lu\n", td);
            RedBlackBStree_print(tree);
        }
        printf("[Usuwanie losowego ciągu kluczy]\n");
        sleep(1);
        for(size_t i = 0; i<50; i++){
            uint64_t td = genRandLong(&r)%50 + 1;
            RB_BSTree_delete(tree, td);
            printf("Delete %lu\n", td);
            RedBlackBStree_print(tree);
        }
        RB_BSTree_clean(tree);
    }
    else if(strcmp(argv[1], "splay")==0){
        printf("[Dodawanie rosnącego ciągu kluczy]\n");
        sleep(1);
        Splay_node* root = NULL;
        for (uint64_t i = 1; i <= 50; ++i) {
            root = Splay_insert(root, i);
            printf("Insert %lu\n", i);
            Splay_print(root);
        }

        printf("[Usuwanie losowego ciągu kluczy]\n");
        sleep(1);
        for(size_t i = 0; i<50; i++){
            uint64_t td = genRandLong(&r)%50 + 1;
            root = Splay_delete(root, td);
            printf("Delete %lu\n", td);
            Splay_print(root);
        }
        Splay_clean(root);

        printf("[Dodawanie losowego ciągu kluczy]\n");
        sleep(1);
        root = NULL;
        for (uint64_t i = 1; i <= 50; ++i) {
            uint64_t td = genRandLong(&r)%50 + 1;
            root = Splay_insert(root, td);
            printf("Insert %lu\n", td);
            Splay_print(root);
        }
        printf("[Usuwanie losowego ciągu kluczy]\n");
        sleep(1);
        for(size_t i = 0; i<50; i++){
            uint64_t td = genRandLong(&r)%50 + 1;
            root = Splay_delete(root, td);
            printf("Delete %lu\n", td);
            Splay_print(root);
        }
        Splay_clean(root);
    }


    return 0;
}
