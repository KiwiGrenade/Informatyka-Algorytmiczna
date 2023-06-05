//
// Created by mango on 04.06.23.
//

#ifndef AISD_4_RB_BST_H
#define AISD_4_RB_BST_H

#include <iostream>

struct Node
{
    bool isRed = true;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    size_t key;
};

class RB_BST {
private:
    void leftRotate(Node* x) noexcept;
    void rightRotate(Node* x) noexcept;
    void transplant(Node* u, Node* v) noexcept;
    Node * minimum(Node* x) noexcept;
    void deleteFixUp(Node* x) noexcept;
    void insertFixUp(Node *z) noexcept;
public:

    Node* NIL;
    Node* root;
    RB_BST() noexcept;
    ~RB_BST() noexcept;
    void insert(size_t val) noexcept;
    void deleteFirstOf(size_t val) noexcept;
    Node* iterativeTreeSearch(Node* x, size_t k) noexcept;
    void print(Node *node, int depth, char prefix, char *leftTrace, char *rightTrace) noexcept;
    size_t height(Node *node) noexcept;
    void deleteTree(Node *node) noexcept;
};


#endif //AISD_4_RB_BST_H
