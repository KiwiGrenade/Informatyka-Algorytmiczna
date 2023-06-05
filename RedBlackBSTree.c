#include "stdio.h"

#include "RedBlackBSTree.h"
#include "queue.h"


static RB_BST_node* RB_new_node(uint64_t data){
    RB_BST_node* node = malloc(sizeof(*node));
    *node = (RB_BST_node){
        .data = data,
        .parent = NULL, .left = NULL, .right = NULL,
        .color = RED
    };
    return node;
}

static RB_BST_node* minValueNode(RB_tree* T, RB_BST_node* node) {
    while (node->left != T->NIL)
        node = node->left;
    return node;
}


// Replace node u with node v
static void replace_nodes(RB_tree* T, RB_BST_node* u, RB_BST_node* v) {
    if (u->parent == T->NIL)
        T->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}


static void print_BST(RB_tree* T, RB_BST_node* root, int depth,char prefix, char* left_trace, char* right_trace){
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
    printf("\033[0;%dm [%lu]\033[0m\n", c,root->data);
    left_trace[depth]=' ';
    if( root->right != T->NIL ){
        right_trace[depth]='|';
        print_BST(T, root->right, depth+1, '\\', left_trace, right_trace);
    }
}


// Function to perform left rotation
static void leftRotate(RB_tree* T, RB_BST_node* x) {
    RB_BST_node* y = x->right;
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
static void rightRotate(RB_tree* T, RB_BST_node* y) {
    RB_BST_node* x = y->left;
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
static void fixViolation_insert(RB_tree* T, RB_BST_node* z) {
    while(z->parent->color == RED) {
        if(z->parent == z->parent->parent->left) { //z.parent is the left child

            RB_BST_node* y = z->parent->parent->right; //uncle of z

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
            RB_BST_node* y = z->parent->parent->left;

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

static void fixViolation_delete(RB_tree* T, RB_BST_node* x){
    while (x != T->root && x->color == BLACK) {
        if (x == x->parent->left) {
            RB_BST_node* w = x->parent->right;
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
            RB_BST_node* w = x->parent->left;
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

void RB_BSTree_delete(RB_tree* T, uint64_t data)
{
    RB_BST_node* z = T->root;
    while (z != T->NIL) {
        if (data < z->data)
            z = z->left;
        else if (data > z->data)
            z = z->right;
        else
            break;
    }

    if (z == T->NIL)
        return;

    RB_BST_node* y = z;
    color_t y_col = y->color;
    RB_BST_node* x;
    if(z->left == T->NIL){
        x = z->right;
        replace_nodes(T, z, z->right);
    } else if(z->right == T->NIL){
        x = z->left;
        replace_nodes(T, z, z->left);
    } else{
        y = minValueNode(T, z->right);
        y_col = y->color;
        x = y->right;
        if(y->parent == z)
            x->parent = y;
        else{
            replace_nodes(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        replace_nodes(T, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
   if(y_col == BLACK)
       fixViolation_delete(T, x);
}


// Function to insert a node in the Red-Black Tree
void RB_BSTree_insert(RB_tree* T, uint64_t data) {
    RB_BST_node* z = RB_new_node(data);

    RB_BST_node* y = T->NIL;
    RB_BST_node* temp = T->root;

    while(temp != T->NIL) {
        y = temp;
        if(z->data < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }
    z->parent = y;

    if(y == T->NIL) { //newly added node is root
        T->root = z;
    }
    else if(z->data < y->data) //data of child is less than its parent, left child
        y->left = z;
    else
        y->right = z;

    z->right = T->NIL;
    z->left = T->NIL;

    fixViolation_insert(T, z);
}

size_t RB_BSTree_height(RB_tree* T)
{
    Queue* queue = NULL;
    size_t height = 0;
    size_t node_count;
    RB_BST_node* cur;

    if(T->root == T->NIL)
        return 0;

    queue_enqueue(&queue, T->root);
    while (!queue_empty(queue))
    {
        height++;
        node_count = queue_size(queue);
        while (node_count--){
            cur = queue_front(queue);
            if(cur->left != T->NIL)
                queue_enqueue(&queue ,cur->left);
            if(cur->right != T->NIL)
                queue_enqueue(&queue, cur->right);

            queue_dequeue(&queue);
        }
    }
    return height;
}


void RB_BSTree_clean(RB_tree* T)
{
    Queue* queue = NULL;
    size_t node_count;
    RB_BST_node* cur;

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
            cur = queue_front(queue);
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

void RedBlackBStree_print(RB_tree* T){
    char* right_trace = malloc(100 * sizeof(char));
    char* left_trace = malloc(100 * sizeof(char));
    print_BST(T,T->root, 0, '-', left_trace, right_trace);
    size_t h = RB_BSTree_height(T);
    for (size_t i = 0; i < h; ++i) {
        printf("====");
    }
    printf("\n");
    free(right_trace);
    free(left_trace);
}
