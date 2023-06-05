//
// Created by mango on 03.06.23.
//

#ifndef AISD_4_BST_H
#define AISD_4_BST_H

#include <iostream>

struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    size_t key;
};

class BST {
private:
    static Node* successor(Node* x) noexcept;
    static Node* iterativeTreeSearch(Node* x, size_t k) noexcept;
    static Node* minimum(Node* x) noexcept;
    static Node* maximum(Node* x) noexcept;
    void deleteTree(Node *node) noexcept;

public:
    Node* root;
    ~BST() noexcept;
    void insert(size_t val) noexcept;
    Node * deleteFirstOf(size_t val) noexcept;
    size_t height(Node *node) noexcept;
    void print(Node *node, int depth, char prefix, char *leftTrace, char *rightTrace) noexcept;
};


#endif //AISD_4_BST_H
