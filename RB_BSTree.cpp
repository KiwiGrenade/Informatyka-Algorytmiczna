#include "stdio.h"

#include "RB_BSTree.h"
#include "queue.h"


static Node* newNode(size_t data){
    Node* node = static_cast<Node *>(malloc(sizeof(Node)));
    *node = (Node){
        .key = data,
            .left = NULL,  .right = NULL,.parent = NULL,
        .color = RED
    };
    return node;
}

static Node* minimum(RBTree* T, Node* node) {
    while (node->left != T->NIL)
        node = node->left;
    return node;
}


// Replace node u with node v
static void transplant(RBTree* T, Node* u, Node* v) {
    if (u->parent == T->NIL)
        T->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}


static void print_BST(RBTree* T, Node* root, int depth, char prefix, char* left_trace, char* right_trace){
    if( root == T->NIL ) return;
    if( root->left != T->NIL ){
        print_BST(T, root->left, depth+1, '/', left_trace, right_trace);
    }
    if(prefix == '/') left_trace[depth-1]='|';
    if(prefix == '\\') right_trace[depth-1]=' ';
    if( depth==0) printf("-");
    if( depth>0) printf(" ");
    for(int i=0; i<depth-1; i++)
        if( left_trace[i]== '|' || right_trace[i]=='|' ) {
            printf("| ");
        } else {
            printf("  ");
        }
    if( depth>0 ) printf("%c-", prefix);
    int c;
    if (root->color == RED)
        c = 31;
    else
        c = 37;
    printf("\033[0;%dm [%lu]\033[0m\n", c,root->key);
    left_trace[depth]=' ';
    if( root->right != T->NIL ){
        right_trace[depth]='|';
        print_BST(T, root->right, depth+1, '\\', left_trace, right_trace);
    }
}


// Function to perform left rotation
static void leftRotate(RBTree* T, Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left != T->NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == T->NIL)
        T->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Function to perform right rotation
static void rightRotate(RBTree* T, Node* y) {
    Node* x = y->left;
    y->left = x->right;

    if (x->right != T->NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == T->NIL)
        T->root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

// Function to fix the Red-Black Tree properties after insertion
static void insertFixUp(RBTree* T, Node* z) {
    while(z->parent->color == RED) {
        if(z->parent == z->parent->parent->left) { //z.parent is the left child

            Node* y = z->parent->parent->right; //uncle of z

            if(y->color == RED) { //case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if(z == z->parent->right) {
                    z = z->parent;
                    leftRotate(T, z);
                }
                //case3
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(T, z->parent->parent);
            }
        }
        else {
            Node* y = z->parent->parent->left;

            if(y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if(z == z->parent->left) {
                    z = z->parent;
                    rightRotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK;
}

static void deleteFixUp(RBTree* T, Node* x){
    while (x != T->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(T, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(T, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(T, x->parent);
                x = T->root;
            }
        } else{
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(T, x->parent);
                w = x->parent->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(T, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(T, x->parent);
                x = T->root;
            }
        }
    }
    x->color = BLACK;
}

void nodeDelete(RBTree* T, size_t key)
{
    Node* z = T->root;
    while (z != T->NIL) {
        if (key < z->key)
            z = z->left;
        else if (key > z->key)
            z = z->right;
        else
            break;
    }

    if (z == T->NIL)
        return;

    Node* y = z;
    color_t y_col = y->color;
    Node* x;
    if(z->left == T->NIL){
        x = z->right;
        transplant(T, z, z->right);
    } else if(z->right == T->NIL){
        x = z->left;
        transplant(T, z, z->left);
    } else{
        y = minimum(T, z->right);
        y_col = y->color;
        x = y->right;
        if(y->parent == z)
            x->parent = y;
        else{
            transplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
   if(y_col == BLACK)
       deleteFixUp(T, x);
}


// Function to insert a node in the Red-Black Tree
void insert(RBTree* T, size_t data) {
    Node* z = newNode(data);

    Node* y = T->NIL;
    Node* temp = T->root;

    while(temp != T->NIL) {
        y = temp;
        if(z->key < temp->key)
            temp = temp->left;
        else
            temp = temp->right;
    }
    z->parent = y;

    if(y == T->NIL) { //newly added node is root
        T->root = z;
    }
    else if(z->key < y->key) //key of child is less than its parent, left child
        y->left = z;
    else
        y->right = z;

    z->right = T->NIL;
    z->left = T->NIL;

    insertFixUp(T, z);
}

size_t height(RBTree* T)
{
    Queue* queue = NULL;
    size_t height = 0;
    size_t node_count;
    Node* cur;

    if(T->root == T->NIL)
        return 0;

    queue_enqueue(&queue, T->root);
    while (!queue_empty(queue))
    {
        height++;
        node_count = queue_size(queue);
        while (node_count--){
            cur = static_cast<Node *>(queue_front(queue));
            if(cur->left != T->NIL)
                queue_enqueue(&queue ,cur->left);
            if(cur->right != T->NIL)
                queue_enqueue(&queue, cur->right);

            queue_dequeue(&queue);
        }
    }
    return height;
}


void BSClean(RBTree* T)
{
    Queue* queue = NULL;
    size_t node_count;
    Node* cur;

    if(T->root == T->NIL)
    {
        free(T->NIL);
        free(T);
        return;
    }

    queue_enqueue(&queue, T->root);
    while (!queue_empty(queue))
    {
        node_count = queue_size(queue);
        while (node_count--){
            cur = static_cast<Node *>(queue_front(queue));
            if(cur == NULL)
                continue;
            if(cur->left != T->NIL)
                queue_enqueue(&queue ,cur->left);
            if(cur->right != T->NIL)
                queue_enqueue(&queue, cur->right);

            queue_dequeue(&queue);
            free(cur);
        }
    }
    free(T->NIL);
    free(T);
}

void print(RBTree* T){
    char* right_trace = static_cast<char *>(malloc(100 * sizeof(char)));
    char* left_trace = static_cast<char *>(malloc(100 * sizeof(char)));
    print_BST(T,T->root, 0, '-', left_trace, right_trace);
    size_t h = height(T);
    for (size_t i = 0; i < h; ++i) {
        printf("====");
    }
    printf("\n");
    free(right_trace);
    free(left_trace);
}
