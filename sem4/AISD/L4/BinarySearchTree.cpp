#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "BinarySearchTree.h"


// global variables used in `print_BST`
static char* left_trace; // needs to be allocaded with size
static char* right_trace; // needs to be allocaded with size

long long comparisions = 0;
long long swapOrView = 0;

bool compare(int a, int b){
    comparisions++;
    return a < b;
}

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
    printf("[%lu]\n", root->key);
    left_trace[depth]=' ';
    if( root->right != NULL ){
        right_trace[depth]='|';
        print_BST(root->right, depth+1, '\\');
    }
}


BSTree_node* BST_insert(BSTree_node* root, uint64_t val)
{
    BSTree_node* node = static_cast<BSTree_node *>(malloc(sizeof(*node)));
    *node = (BSTree_node){.key = val,
            .left = NULL,
            .right = NULL

    };

    swapOrView++;
    if(root == NULL)
        return node;

    BSTree_node* cur = root;
    while (1){
        if(compare(val, cur->key)){
            swapOrView+=2;
            if(cur->left == NULL){
                cur->left = node;
                break;
            } else
                cur = cur->left;
        } else{
            swapOrView+=2;
            if(cur->right == NULL){
                cur->right = node;
                break;
            } else
                cur = cur->right;
        }
    }
    return root;
}

BSTree_node* BST_delete(BSTree_node* root, uint64_t key)
{
    swapOrView++;
    if (root == NULL) {
        return root;
    }

    BSTree_node* current = root;
    BSTree_node* parent = NULL;

    swapOrView++;
    while (current != NULL && current->key != key) {
        parent = current;

        swapOrView++;
        if (compare(key , current->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    swapOrView++;
    if (current == NULL)
        // Value not found
        return root;


    swapOrView+=2;
    if (current->left == NULL && current->right == NULL) {
        // Case 1: Node have no kids
        swapOrView+=2;
        if (parent == NULL) {
            root = NULL;
        } else if (parent->left == current) {
            swapOrView++;
            parent->left = NULL;
        } else {
            swapOrView++;
            parent->right = NULL;
        }

        free(current);
    }
    else if (current->left == NULL) {
        swapOrView+=3;
        // Case 2.1: Node have only right kid
        BSTree_node* tmp = current;
        if (parent == NULL) {
            root = current->right;
        } else if (parent->left == current) {
            swapOrView++;
            parent->left = current->right;
        } else {
            swapOrView++;
            parent->right = current->right;
        }
        free(tmp);
    } else if (current->right == NULL) {
        swapOrView+=4;
        // Case 2.2: Node have only left kid
        BSTree_node* temp = current;
        if (parent == NULL) {
            root = current->left;
        } else if (parent->left == current) {
            swapOrView++;
            parent->left = current->left;
        } else {
            swapOrView++;
            parent->right = current->left;
        }
        free(temp);
    } else {
        swapOrView+=4;
        // Case 3: Node have both kids
        BSTree_node* successorParent = current;
        BSTree_node* successor = current->right;

        swapOrView++;
        while (successor->left != NULL) {
            swapOrView++;
            successorParent = successor;
            successor = successor->left;
        }

        current->key = successor->key;

        swapOrView+=2;
        if (successorParent->left == successor) {
            successorParent->left = successor->right;
        } else {
            successorParent->right = successor->right;
        }

        free(successor);
    }

    return root;
}

void BST_clean(BSTree_node* root){
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
            cur = static_cast<BSTree_node *>(queue_front(queue));
            if(cur->left != NULL)
                queue_enqueue(&queue ,cur->left);
            if(cur->right != NULL)
                queue_enqueue(&queue, cur->right);

            queue_dequeue(&queue);
            free(cur);
        }
    }
}

size_t BST_height(BSTree_node* root){
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
            cur = static_cast<BSTree_node *>(queue_front(queue));
            if(cur->left != NULL)
                queue_enqueue(&queue ,cur->left);
            if(cur->right != NULL)
                queue_enqueue(&queue, cur->right);

           queue_dequeue(&queue);
        }
    }
    return height;
}


void BST_print(BSTree_node * root)
{
    right_trace = static_cast<char *>(malloc(50 * sizeof(char)));
    left_trace = static_cast<char *>(malloc(50 * sizeof(char)));
    print_BST(root, 0, '-');
    size_t h = BST_height(root);
    for (size_t i = 0; i < h; ++i) {
        printf("====");
    }
    printf("\n");
    free(left_trace);
    free(right_trace);
}
