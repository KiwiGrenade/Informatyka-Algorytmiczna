#include "RB_BST.h"

int comparisions = 0;
bool compare(int a, int b){
    comparisions++;
    return a < b;
}

int swapOrView = 0;

RB_BST::RB_BST() noexcept
{
    NIL = new Node{false, nullptr, nullptr, nullptr, 0};
    root = NIL;
}

void RB_BST::leftRotate(Node *x) noexcept
{
    swapOrView++;
    Node* y = x->right;
    x->right = y->left;

    swapOrView++;
    if (y->left != NIL)
        y->left->parent = x;

    swapOrView++;
    y->parent = x->parent;

    swapOrView++;
    swapOrView++;
    if (x->parent == NIL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    swapOrView++;
    swapOrView++;
    y->left = x;
    x->parent = y;
}
void RB_BST::rightRotate(Node *x) noexcept
{
    swapOrView++;
    Node* y = x->left;
    x->left = y->right;

    swapOrView++;
    if(y->right != NIL)
        y->right->parent = x;

    swapOrView++;
    y->parent = x->parent;

    swapOrView++;
    swapOrView++;
    if (x->parent == NIL)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    swapOrView++;
    swapOrView++;
    y->right = x;
    x->parent = y;
}
void RB_BST::insert(size_t val) noexcept
{
    Node* z = new Node{.key = val};
    Node* y = NIL;
    Node* x = root;

    while(x != NIL)
    {
        swapOrView++;
        y = x;
        if(compare(z->key, x->key))
            x = x->left;
        else
            x = x->right;
    }

    swapOrView++;
    z->parent = y;

    swapOrView++;
    swapOrView++;
    if (y == NIL)
        root = z;
    else if(compare(z->key, y->key))
        y->left = z;
    else
        y->right = z;

    swapOrView++;
    swapOrView++;
    z->right = NIL;
    z->left = NIL;

    insertFixUp(z);
}

void RB_BST::insertFixUp(Node *z) noexcept
{
    while (z->parent->isRed)
    {
        swapOrView++;
        swapOrView++;
        if(z->parent == z->parent->parent->left)
        {
            swapOrView++;
            Node* y = z->parent->parent->right;
            if (y->isRed)
            {
                swapOrView++;
                swapOrView++;
                swapOrView++;
                swapOrView++;
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true;
                z = z->parent->parent;
            }
            else
            {
                swapOrView++;
                if (z == z->parent->right)
                {
                    swapOrView++;
                    z = z->parent;
                    leftRotate(z);
                }
                swapOrView++;
                swapOrView++;
                z->parent->isRed = false;
                z->parent->parent->isRed = true;
                rightRotate(z->parent->parent);
            }
        }
        else
        {
            swapOrView++;
            Node* y = z->parent->parent->left;
            if (y->isRed)
            {
                swapOrView++;
                swapOrView++;
                swapOrView++;
                swapOrView++;
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    swapOrView++;
                    z = z->parent;
                    rightRotate(z);
                }
                swapOrView++;
                swapOrView++;
                z->parent->isRed = false;
                z->parent->parent->isRed = true;
                leftRotate(z->parent->parent);
            }
        }
    }
    swapOrView++;
    root->isRed = false;
}

void RB_BST::deleteFirstOf(size_t val) noexcept
{
    swapOrView++;
    Node* z = root;
    while(z != NIL)
    {
        swapOrView++;
        if(compare(val, z->key)) {
            swapOrView++;
            z = z->left;
        }
        else if(compare(z->key,val)) {
            swapOrView++;
            z = z->right;
        }
        else
            break;
    }

    swapOrView++;
    if(z == NIL)
        return;

    swapOrView++;
    Node* y = z;
    bool yOriginalColor = y->isRed;
    Node* x;

    swapOrView++;
    if(z->left == NIL)
    {
        swapOrView++;
        x = z->right;
        transplant(z, z->right);
    }
    else if(z->right == NIL)
    {
        swapOrView++;
        swapOrView++;
        x = z->left;
        transplant(z, z->left);
    }
    else
    {
        swapOrView++;
        y = minimum(z->right);
        yOriginalColor = y->isRed;
        x = y->right;

        swapOrView++;
        if(y->parent == z) {
            swapOrView++;
            x->parent = z;
        }
        else
        {
            swapOrView++;
            swapOrView++;
            transplant( y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        swapOrView++;
        swapOrView++;
        swapOrView++;
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->isRed = z->isRed;
    }
    if(yOriginalColor == false)
        deleteFixUp(x);
}

void RB_BST::deleteFixUp(Node *x) noexcept
{
    while(x != root && !x->isRed)
    {
        swapOrView++;
        swapOrView++;
        if(x == x->parent->left)
        {
            swapOrView++;
            Node *w = x->parent->right;
            if(w->isRed)
            {
                swapOrView++;
                swapOrView++;
                swapOrView++;
                w->isRed = false;
                x->parent->isRed = true;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            swapOrView++;
            if(!w->left->isRed && !w->right->isRed)
            {
                swapOrView++;
                swapOrView++;
                w->isRed = true;
                x = x->parent;
            }
            else
            {
                swapOrView++;
                if(!w->right->isRed)
                {
                    swapOrView++;
                    swapOrView++;
                    swapOrView++;
                    w->left->isRed = false;
                    w->isRed = true;
                    rightRotate(w);
                    w = x->parent->right;
                }
                swapOrView++;
                swapOrView++;
                swapOrView++;
                swapOrView++;
                w->isRed = x->parent->isRed;
                x->parent->isRed = false;
                w->right->isRed = false;
                leftRotate(x->parent);
                x = root;
            }
        }
        else
        {
            swapOrView++;
            Node *w = x->parent->left;
            if(w->isRed)
            {
                swapOrView++;
                swapOrView++;
                swapOrView++;
                w->isRed = false;
                x->parent->isRed = true;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            swapOrView++;
            if(!w->right->isRed && !w->left->isRed)
            {
                swapOrView++;
                swapOrView++;
                w->isRed = true;
                x = x->parent;
            }
            else
            {
                swapOrView++;
                if(!w->left->isRed)
                {
                    swapOrView++;
                    swapOrView++;
                    swapOrView++;
                    w->right->isRed = false;
                    w->isRed = true;
                    leftRotate(w);
                    w = x->parent->left;
                }
                swapOrView++;
                swapOrView++;
                swapOrView++;
                swapOrView++;
                w->isRed = x->parent->isRed;
                x->parent->isRed = false;
                w->left->isRed = false;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    swapOrView++;
    x->isRed = false;
}

void RB_BST::transplant(Node *u, Node *v) noexcept
{
    swapOrView++;
    if (u->parent == NIL) {
        swapOrView++;
        root = v;
    }
    else if (u == u->parent->left) {
        swapOrView++;
        swapOrView++;
        u->parent->left = v;
    }
    else {
        swapOrView++;
        u->parent->right = v;
    }
    swapOrView++;
    v->parent = u->parent;
}

Node *RB_BST::iterativeTreeSearch(Node *x, size_t k) noexcept
{
    swapOrView++;
    while(x != NIL && k != x->key)
    {
        swapOrView++;
        if(compare(k, x->key))
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

Node * RB_BST::minimum(Node *x) noexcept
{
    while (x->left != NIL)
        swapOrView++;
        swapOrView++;
        x = x->left;
    return x;
}


void RB_BST::print(Node *node, int depth, char prefix, char *leftTrace, char *rightTrace) noexcept
{
    if (node == NIL || node == nullptr|| leftTrace == nullptr || rightTrace == nullptr)
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
//
RB_BST::~RB_BST() noexcept
{
    deleteTree(root);
}
