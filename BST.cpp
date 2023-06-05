//
// Created by mango on 03.06.23.
//

#include "BST.h"

void BST::insert(size_t val) noexcept
{
    Node* y = nullptr;
    Node* x = root;
    Node* z = new Node;

    z->key = val;

    while(x != nullptr)
    {
        y = x;
        if(z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == nullptr)
        root = z;
    else if(z->key < y->key)
        y->left = z;
    else
        y->right = z;
}

Node * BST::deleteFirstOf(size_t val) noexcept
{
    Node* z = iterativeTreeSearch(root, val);
    if(z == nullptr)
    {
        return nullptr;
    }

    Node *y, *x;

    if(z->left == nullptr || z->right == nullptr)
        y = z;
    else
        y = successor(z);


    if(y->left != nullptr)
        x = y->left;
    else
        x = y->right;
    if(x != nullptr)
        x->parent = y->parent;

    if (y->parent == nullptr)
        root = x;
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    if (y != z)
        z->key = y->key;

    return y;
}

size_t BST::height(Node *node) noexcept
{
    if(root == nullptr)
        return 0;

    size_t hLeft = height(node->left);
    size_t hRight = height(node->right);

    if(hLeft > hRight)
        return hLeft + 1;
    else
        return hRight + 1;
}

Node *BST::iterativeTreeSearch(Node *x, size_t k) noexcept
{
    while(x != nullptr && k != x->key)
    {
        if(k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

Node *BST::successor(Node *x) noexcept
{
    if(x->right != nullptr)
        return minimum(x->right);

    Node* y = x->parent;
    while(y != nullptr && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

Node *BST::minimum(Node *x) noexcept
{
    while (x->left != nullptr)
        x = x->left;
    return x;
}

Node *BST::maximum(Node *x) noexcept
{
    while (x->right != nullptr)
        x = x->right;
    return x;
}

void BST::print(Node *node, int depth, char prefix, char *leftTrace, char *rightTrace) noexcept
{
    if (node == nullptr || leftTrace == nullptr || rightTrace == nullptr)
        return;
    if (node->left != nullptr)
        print(node->left, depth + 1, '/', leftTrace, rightTrace);
    if (prefix == '/')
        leftTrace[depth-1] = '|';
    if (prefix == '\\')
        rightTrace[depth-1] = ' ';
    if (depth == 0)
        std::printf("-");
    if (depth > 0)
        std::printf(" ");
    for (int i = 0; i < depth - 1; ++i)
    {
        if (leftTrace[i] == '|' || rightTrace[i] == '|')
            printf("| ");
        else
            printf("  ");
    }
    if (depth > 0)
        printf("%c-", prefix);
    printf("[%zu]\n", node->key);
    leftTrace[depth]=' ';
    if( node->right != nullptr ){
        rightTrace[depth]='|';
        print(node->right, depth + 1, '\\', leftTrace, rightTrace);
    }
}

BST::~BST() noexcept
{
    deleteTree(root);
}

void BST::deleteTree(Node *node) noexcept
{
    if(node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}
