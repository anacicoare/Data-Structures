#include <stdlib.h>
#include <stdio.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define abs(a) \
   ({ __typeof__ (a) _a = (a); \
     _a > 0 ? _a : -_a; })

typedef struct BTNode {
    int data;
    struct BTNode *parent;
    struct BTNode *left;
    struct BTNode *right;
} BTNode;

BTNode* initNode(int value) {
    BTNode* node = (BTNode*)malloc(sizeof(BTNode));

    if (node == NULL) {
        return NULL;
    }
    node->data = value;
    node->left = node->right = node->parent = NULL;

    return node;
}

void destroyTree(BTNode** root) {
    if (*root == NULL) {
        return;
    }

    // erase left subtree
    destroyTree(&(*root)->left);

    // erase right subtree
    destroyTree(&(*root)->right);

    // erase current node
    free(*root);

    *root = NULL;
}

int isLeaf(BTNode* node) {
    return (node->left == NULL
        && node->right == NULL);
}

int getNodeDegrees(BTNode* node) {
    return (node->left != NULL) + (node->right != NULL);
}

BTNode* insertNode(BTNode* root, int value) {
    
    if (root == NULL)
    {
        BTNode* new_node = initNode(value);
        root = new_node;
        return root;
    }
    else
    {
        if (value > root->data)
        {
            if (root->right == NULL)
            {
                BTNode* new_node = initNode(value);
                root->right = new_node;
                new_node->parent = root;
            }
            return insertNode(root->right, value);
        }

        if (value < root->data)
        {
            if (root->left == NULL)
            {
                BTNode* new_node = initNode(value);
                root->left = new_node;
                new_node->parent = root;
            }
            return insertNode(root->left, value);
        }
    }

    return NULL;
}

BTNode* searchNode(BTNode* root, int value) {

    if (root == NULL)
        return NULL;

    if (value == root->data)
        return root;

    if (value > root->data)
        return searchNode(root->right, value);

    if (value < root->data)
        return searchNode(root->left, value);

    return NULL;
}

BTNode* find_most_left(BTNode* starting_node)
{
    if (starting_node->left == NULL)
        return starting_node;
    else
        return find_most_left(starting_node->left);
}

int removeNode(BTNode** root, BTNode* node) 
{
    BTNode* parent, *child_left, *child_right, *inorder_node, *child;
    int left = 0, right = 0;
    if (node == NULL)
    {
        printf("node does not exist");
        return -1;
    }
    if (isLeaf(node)) 
    {
        parent = node->parent;
        
        if (node->data < parent->data)
        {
            parent->left = NULL;
            free(node);
        }

        if (node->data > parent->data)
        {
            parent->right = NULL;
            free(node);
        }
        
        return 0;
    }
    else
        if (node->left != NULL && node->right != NULL)
        {
            parent = node->parent;
            inorder_node = find_most_left(node->right);
     
            int aux, initial_node, initial_inorder;

            if (isLeaf(inorder_node))
            {
                parent = inorder_node->parent;

                if (inorder_node->data < parent->data)
                {

                    aux = node->data;
                    node->data = inorder_node->data;
                    inorder_node->data = aux;
                    //swap data

                    parent->left = NULL;
                    free(inorder_node);
                }

                if (inorder_node->data > parent->data)
                {
                    aux = node->data;
                    node->data = inorder_node->data;
                    inorder_node->data = aux;
                    //swap data

                    parent->right = NULL;
                    free(inorder_node);
                }

                return 0;
            }
           
            if (inorder_node->right != NULL)
            {
                parent = inorder_node->parent;
                child_right = inorder_node->right;

                parent->left = child_right;
                child_right->parent = parent;

                aux = node->data;
                node->data = inorder_node->data;
                inorder_node->data = aux;
                //swap data

                free(inorder_node);
            }

        }
        else
            if (node->left != NULL)
            {
                parent = node->parent;

                child_left = node->left;
                if (node->data <= parent->data)
                {
                    parent->left = child_left;
                    child_left->parent = parent;

                    free(node);
                    return 0;
                }

                child_right = node->right;
                if (node->data > parent->data)
                {
                    parent->right = child_right;
                    child_right->parent = parent;

                    free(node);
                    return 0;
                }
                return 0;
            }
            else
                if (node->right != NULL)
                {
                    parent = node->parent;

                    child_left = node->right;
                    if (node->data <= parent->data)
                    {
                        parent->left = child_left;
                        child_left->parent = parent;

                        free(node);
                        return 0;
                    }

                    child_right = node->right;
                    if (node->data > parent->data)
                    {
                        parent->right = child_right;
                        child_right->parent = parent;

                        free(node);
                        return 0;
                    }

                    return 0;
                }

    return 0;
}

void printInOrder(BTNode* root) {

    if (root == NULL)
        return;
    printInOrder(root->left);
    printf("%d ", root->data);
    printInOrder(root->right);
}

void printPreOrder(BTNode* root) {

    if (root == NULL)
        return;
    printf("%d ", root->data);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printPostOrder(BTNode* root) {

    if (root == NULL)
        return;
    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%d ", root->data);
}

size_t getNumberNodes(BTNode* root) {
  
    if (root == NULL)
        return 0;
    return 1 + getNumberNodes(root->left) + getNumberNodes(root->right);
    return 0;
}

void printBFS(BTNode* root) {
   
    if (root == NULL)
        return;

    queue_t* bfs_queue = initQueue();
    
    enqueue(bfs_queue, root);
    
    while (bfs_queue->len != 0)
    {
        BTNode* queue_node = dequeue(bfs_queue);
        printf("%d ", queue_node->data);
        
        if (queue_node->left != NULL)
            enqueue(bfs_queue, queue_node->left);
        
        if (queue_node->right != NULL)
            enqueue(bfs_queue, queue_node->right);
    }

}
