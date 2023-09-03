#include <stdlib.h>
#include <stdio.h>

#include "SplayTree.h"
#include "queue.h"

// global variables used in `print_BST`
static char* left_trace; // needs to be allocaded with size
static char* right_trace; // needs to be allocaded with size


long long comparisions = 0;
long long swapOrView = 0;

bool compare(int a, int b){
    comparisions++;
    return a < b;
}


static void print_BST(Splay_node* root, int depth,char prefix){
    if( root == NULL ) return;
    if( root->left != NULL ){
        print_BST(root->left, depth+1, '/');
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
    printf("[%lu]\n", root->data);
    left_trace[depth]=' ';
    if( root->right != NULL ){
        right_trace[depth]='|';
        print_BST(root->right, depth+1, '\\');
    }
}

static Splay_node* rotate_left(Splay_node* x) {
    Splay_node* y = x->right;
    x->right = y->left;
    y->left = x;

    swapOrView += 2;

    return y;
}

static Splay_node* rotate_right(Splay_node* x) {
    Splay_node* y = x->left;
    x->left = y->right;
    y->right = x;
    swapOrView += 2;
    return y;
}

static Splay_node* splay(Splay_node* root, size_t key)
{
    if (root == NULL || root->data == key)
        return root;

    Splay_node* dummy_node = static_cast<Splay_node *>(malloc(sizeof(Splay_node))); // Dummy node to simplify rotations
    dummy_node->left = dummy_node->right = NULL;
    Splay_node* left_max = dummy_node;
    Splay_node* right_min = dummy_node;
    Splay_node* current = root;
    swapOrView++;

    while (1) {
        if (compare(key, current->data)) {
            swapOrView++;
            if (current->left == NULL)
                break;
            swapOrView++;
            if (compare(key, current->left->data)) {
                current = rotate_right(current);
                swapOrView++;
                if (current->left == NULL)
                    break;
            }
            swapOrView++;
            swapOrView++;
            right_min->left = current;
            right_min = current;
            current = current->left;
        } else if (compare(current->data, key)) {
            swapOrView++;
            if (current->right == NULL)
                break;
            if (compare(current->right->data, key)) {
                current = rotate_left(current);
                swapOrView++;
                if (current->right == NULL)
                    break;
            }
            swapOrView++;
            swapOrView++;
            left_max->right = current;
            left_max = current;
            current = current->right;
        } else {
            break;
        }
    }

    swapOrView++;
    swapOrView++;
    swapOrView++;
    swapOrView++;
    left_max->right = current->left;
    right_min->left = current->right;
    current->left = dummy_node->right;
    current->right = dummy_node->left;
    free(dummy_node);

    return current;
}

Splay_node* Splay_insert(Splay_node* root, size_t data) {
    if (root == NULL) {
        swapOrView++;
        swapOrView++;
        swapOrView++;
        Splay_node* newNode= static_cast<Splay_node *>(malloc(sizeof(Splay_node)));
        *newNode= (Splay_node){
            .data = data, .left = NULL ,.right = NULL
        };
        return newNode;
    }

    root = splay(root, data);


    swapOrView++;
    swapOrView++;
    swapOrView++;
    Splay_node* new_node = static_cast<Splay_node *>(malloc(sizeof(Splay_node)));
    *new_node = (Splay_node){
            .data = data, .left =NULL, .right =NULL
    };

    comparisions++;
    if (data <= root->data) {
        swapOrView++;
        swapOrView++;
        new_node->left = root->left;
        new_node->right = root;
        root->left = NULL;
    } else {
        swapOrView++;
        swapOrView++;
        new_node->right = root->right;
        new_node->left = root;
        root->right = NULL;
    }

    return new_node;
}

Splay_node* Splay_delete(Splay_node* root, size_t data){
    if (root == NULL)
        return NULL;

    root = splay(root, data);

    comparisions++;
    if (root->data != data)
        return root; // Value not found

    Splay_node* tmp = root;
    swapOrView++;
    if(root->left == NULL) {
        swapOrView++;
        root = root->right;
    }
    else{
        swapOrView++;
        root = splay(root->left, data);
        root->right = tmp->right;
    }
    free(tmp);
    return root;
}

size_t Splay_height(Splay_node* root){
    Queue* queue = NULL;
    size_t height = 0;
    size_t node_count;
    Splay_node * cur;

    if(root == NULL)
        return 0;

    queue_enqueue(&queue, root);
    while (!queue_empty(queue))
    {
        height++;
        node_count = queue_size(queue);
        while (node_count--){
            cur = static_cast<Splay_node *>(queue_front(queue));
            if(cur->left != NULL)
                queue_enqueue(&queue ,cur->left);
            if(cur->right != NULL)
                queue_enqueue(&queue, cur->right);

            queue_dequeue(&queue);
        }
    }
    return height;
}

Splay_node* Splay_search(Splay_node* root, size_t data){
    return splay(root, data);
}


void Splay_print(Splay_node* root){
    right_trace = static_cast<char *>(malloc(50 * sizeof(char)));
    left_trace = static_cast<char *>(malloc(50 * sizeof(char)));
    print_BST(root, 0, '-');
    size_t h = Splay_height(root);
    for (size_t i = 0; i < h; ++i) {
        printf("====");
    }
    printf("\n");
    free(right_trace);
    free(left_trace);
}

void Splay_clean(Splay_node* root){
    Queue* queue = NULL;
    size_t node_count;
    Splay_node* cur;

    if(root == NULL)
        return;

    queue_enqueue(&queue, root);
    while (!queue_empty(queue))
    {
        node_count = queue_size(queue);
        while (node_count--){
            cur = static_cast<Splay_node *>(queue_front(queue));
            if(cur->left != NULL)
                queue_enqueue(&queue ,cur->left);
            if(cur->right != NULL)
                queue_enqueue(&queue, cur->right);

            queue_dequeue(&queue);
            free(cur);
        }
    }
}
