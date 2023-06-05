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
    Node* successor(Node* x) noexcept;
    Node* iterativeTreeSearch(Node* x, size_t k) noexcept;
    Node* minimum(Node* x) noexcept;
    Node* maximum(Node* x) noexcept;
    void deleteTree(Node *node) noexcept;
    bool compare(size_t a, size_t b);

public:
    int swapOrView;
    int comparisions;
    Node* root;
    BST() noexcept;
    ~BST() noexcept;
    void insert(size_t val) noexcept;
    Node * deleteFirstOf(size_t val) noexcept;
    size_t height(Node *node) noexcept;

    void print(Node *node, int depth, char prefix, char *leftTrace, char *rightTrace) noexcept;
};


#endif //AISD_4_BST_H
