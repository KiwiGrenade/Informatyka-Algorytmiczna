//
// Created by mango on 04.06.23.
//

#include "RB_BST.h"

void RB_BST::leftRotate(Node *x) noexcept
{
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RB_BST::rightRotate(Node *x) noexcept
{
    Node* y = x->left;
    x->left = y->right;
    if(y->right != NIL)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}
void RB_BST::insert(size_t val) noexcept
{
    Node* z = new Node;
    z->key = val;
    Node* y = NIL;
    Node* x = root;

    while(x != NIL)
    {
        y = x;
        if(z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == NIL)
        root = z;
    else if(z->key < y->key)
        y->left = z;
    else
        y->right = z;
    z->right = NIL;
    z->left = NIL;

    insertFixUp(z);
}
void RB_BST::insertFixUp(Node *z) noexcept
{
    while (z->parent->isRed)
    {
        if(z->parent == z->parent->parent->left)
        {
            Node* y = z->parent->parent->right;
            if (y->isRed)
            {
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->isRed = false;
                z->parent->parent->isRed = true;
                rightRotate(z->parent->parent);
            }
        }
        else
        {
            Node* y = z->parent->parent->left;
            if (y->isRed)
            {
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->isRed = false;
                z->parent->parent->isRed = true;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->isRed = false;
//    z->isRed = true;
//    while(z != root && z->parent->isRed)
//    {
//        if (z->parent == z->parent->parent->left)
//        {
//            Node* y = z->parent->parent->right;
//            if (y->isRed)
//            {
//                z->parent->isRed = false;
//                y->isRed = false;
//                z->parent->parent->isRed = true;
//                z = z->parent->parent;
//            }
//            else
//            {
//                if (z == z->parent->right)
//                {
//                    z = z->parent;
//                    leftRotate(z);
//                }
//                z->parent->isRed = false;
//                z->parent->parent->isRed = true;
//                rightRotate(z->parent->parent);
//            }
//        }
//        else
//        {
//            Node* y = z->parent->parent->left;
//            if (y != NIL && y->isRed)
//            {
//                z->parent->isRed = false;
//                y->isRed = false;
//                z->parent->parent->isRed = true;
//                z = z->parent->parent;
//            }
//            else
//            {
//                if (z == z->parent->left)
//                {
//                    z = z->parent;
//                    rightRotate(z);
//                }
//                z->parent->isRed = false;
//                z->parent->parent->isRed = false;
//                leftRotate(z->parent->parent);
//            }
//        }
//    }
//    root->isRed = false;
}

void RB_BST::deleteFirstOf(size_t val) noexcept
{
    Node* z = iterativeTreeSearch(root, val);
    if(z == NIL)
        return;
    Node *y = z;
    Node *x;
    bool yOriginalColor = y->isRed;
    if(z->left == NIL)
    {
        x = z->right;
        transplant(z, z->right);
    }
    else if(z->right == NIL)
    {
        x = z->left;
        transplant(z, z->left);
    }
    else
    {
        y = minimum(z->right);
        yOriginalColor = y->isRed;
        x = y->right;

        if(y->parent == z)
            x->parent = z;
        else
        {
            transplant( y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->isRed = z->isRed;
    }
    if(yOriginalColor)
        deleteFixUp(x);
}

void RB_BST::deleteFixUp(Node *x) noexcept
{
    while(x != root && !x->isRed)
    {
        if(x == x->parent->left)
        {
            Node *w = x->parent->right;
            if(w->isRed)
            {
                w->isRed = false;
                x->parent->isRed = true;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if(!w->left->isRed && !w->right->isRed)
            {
                w->isRed = true;
                x = x->parent;
            }
            else
            {
                if(!w->right->isRed)
                {
                    w->left->isRed = false;
                    w->isRed = true;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->isRed = x->parent->isRed;
                x->parent->isRed = false;
                w->right->isRed = false;
                leftRotate(x->parent);
                x = root;
            }
        }
        else
        {
            Node *w = x->parent->left;
            if(w->isRed)
            {
                w->isRed = false;
                x->parent->isRed = true;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if(!w->right->isRed && !w->left->isRed)
            {
                w->isRed = true;
                x = x->parent;
            }
            else
            {
                if(!w->left->isRed)
                {
                    w->right->isRed = false;
                    w->isRed = true;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->isRed = x->parent->isRed;
                x->parent->isRed = false;
                w->left->isRed = false;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->isRed = false;
}

void RB_BST::transplant(Node *u, Node *v) noexcept
{
    if (u->parent == NIL)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

Node *RB_BST::iterativeTreeSearch(Node *x, size_t k) noexcept
{
    while(x != NIL && k != x->key)
    {
        if(k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

Node * RB_BST::minimum(Node *x) noexcept
{
    while (x->left != NIL)
        x = x->left;
    return x;
}

void RB_BST::print(Node *node, int depth, char prefix, char *leftTrace, char *rightTrace) noexcept
{
    if (node == NIL || leftTrace == nullptr || rightTrace == nullptr)
        return;
    if (node->left != NIL)
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
    if( node->right != NIL ){
        rightTrace[depth]='|';
        print(node->right, depth + 1, '\\', leftTrace, rightTrace);
    }
}


size_t RB_BST::height(Node *node) noexcept
{
    if(root == NIL)
        return 0;

    size_t hLeft = height(node->left);
    size_t hRight = height(node->right);

    if(hLeft > hRight)
        return hLeft + 1;
    else
        return hRight + 1;
}

void RB_BST::deleteTree(Node *node) noexcept
{
    if(node == NIL)
        return;

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}
RB_BST::~RB_BST() noexcept
{
    deleteTree(root);
}

RB_BST::RB_BST() noexcept
{
    NIL = new Node{false, NIL, NIL, NIL, 0};
    root = NIL;
}
