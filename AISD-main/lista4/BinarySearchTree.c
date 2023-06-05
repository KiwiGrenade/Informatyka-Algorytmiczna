#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "BinarySearchTree.h"


// global variables used in `print_BST`
static char* left_trace; // needs to be allocaded with size
static char* right_trace; // needs to be allocaded with size

static void print_BST(BSTree_node * root, int depth,char prefix){
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


BSTree_node* BSTree_insert(BSTree_node* root, uint64_t data)
{
    BSTree_node* node = malloc(sizeof(*node));
    *node = (BSTree_node){.data = data,
            .right = NULL,
            .left = NULL
    };
    if(root == NULL)
        return node;

    BSTree_node* cur = root;
    while (1){
        if(data < cur->data){
            if(cur->left == NULL){
                cur->left = node;
                break;
            } else
                cur = cur->left;
        } else{
            if(cur->right == NULL){
                cur->right = node;
                break;
            } else
                cur = cur->right;
        }
    }
    return root;
}

BSTree_node* BSTree_delete(BSTree_node* root, uint64_t key)
{
    if (root == NULL) {
        return root;
    }

    BSTree_node* current = root;
    BSTree_node* parent = NULL;

    while (current != NULL && current->data != key) {
        parent = current;

        if (key < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL)
        // Value not found
        return root;


    if (current->left == NULL && current->right == NULL) {
        // Case 1: Node have no kids
        if (parent == NULL) {
            root = NULL;
        } else if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }

        free(current);
    } else if (current->left == NULL) {
        // Case 2.1: Node have only right kid
        BSTree_node* tmp = current;
        if (parent == NULL) {
            root = current->right;
        } else if (parent->left == current) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
        free(tmp);
    } else if (current->right == NULL) {
        // Case 2.2: Node have only left kid
        BSTree_node* temp = current;
        if (parent == NULL) {
            root = current->left;
        } else if (parent->left == current) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
        free(temp);
    } else {
        // Case 3: Node have both kids
        BSTree_node* successorParent = current;
        BSTree_node* successor = current->right;

        while (successor->left != NULL) {
            successorParent = successor;
            successor = successor->left;
        }

        current->data = successor->data;

        if (successorParent->left == successor) {
            successorParent->left = successor->right;
        } else {
            successorParent->right = successor->right;
        }

        free(successor);
    }

    return root;
}

void BSTree_clean(BSTree_node* root){
    Queue* queue = NULL;
    size_t node_count;
    BSTree_node* cur;

    if(root == NULL)
        return;

    queue_enqueue(&queue, root);
    while (!queue_empty(queue))
    {
        node_count = queue_size(queue);
        while (node_count--){
            cur = queue_front(queue);
            if(cur->left != NULL)
                queue_enqueue(&queue ,cur->left);
            if(cur->right != NULL)
                queue_enqueue(&queue, cur->right);

            queue_dequeue(&queue);
            free(cur);
        }
    }
}

size_t BSTree_height(BSTree_node* root){
    Queue* queue = NULL;
    size_t height = 0;
    size_t node_count;
    BSTree_node* cur;

    if(root == NULL)
        return 0;

    queue_enqueue(&queue, root);
    while (!queue_empty(queue))
    {
        height++;
        node_count = queue_size(queue);
        while (node_count--){
            cur = queue_front(queue);
            if(cur->left != NULL)
                queue_enqueue(&queue ,cur->left);
            if(cur->right != NULL)
                queue_enqueue(&queue, cur->right);

           queue_dequeue(&queue);
        }
    }
    return height;
}


void BStree_print(BSTree_node * root)
{
    right_trace = malloc(50* sizeof(char ));
    left_trace = malloc(50* sizeof(char ));
    print_BST(root, 0, '-');
    size_t h = BSTree_height(root);
    for (size_t i = 0; i < h; ++i) {
        printf("====");
    }
    printf("\n");
    free(left_trace);
    free(right_trace);
}
