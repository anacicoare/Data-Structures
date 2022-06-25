#include <stdlib.h>

#define STATUS_OK   0
#define STATUS_ERR  1

typedef struct node {
    int* data; // data field
    struct node* next; // pointer to next node
    struct node* prev; // pointer to prev node
} node_t;

typedef struct dl_list {
    node_t* head; // pointer to head of the list
    node_t* tail; // pointer to end of the list
    size_t len; // list lenght
} list_t;

node_t* init_node(int* value) {
    node_t* new_node = malloc(sizeof(node_t));

    new_node->data = malloc(sizeof(int));
    *new_node->data = *value;

    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

void free_node(node_t* nod)
{
    free(nod->data);
    free(nod);
}

typedef list_t stack_t;

void push(stack_t *stack, int value) {
    /*
     * TODO
     *      ADD A NEW NODE TO THE TOP OF THE STACK
     */
    node_t *new = initNode(value);
    if(stack->len == 0) {
        stack->head = stack->tail = new;
    }
    else {
        new->next = stack->head;
        stack->head->prev = new;
        stack->head = new;
    }
    stack->len ++;
}

int pop(stack_t *stack, int *status) {
    /*
     * TODO
     *      REMOVE THE NODE FROM THE TOP OF THE STACK AND RETURN ITS VALUE
     *          - if stack is empty set status to STATUS_ERR (1)
     *          - else, set status to STATUS_OK (0)
     */

    node_t *elim = stack->head;
    if(stack->len == 0) {
        *status = STATUS_ERR;
        return 0;
    }
    else
        if(stack->len == 1) {
            *status = STATUS_OK;
            node_t *elim = stack->head;
            int x = elim->data;
            stack->head = stack->tail = NULL;
            stack->len --;
            free(elim);
            return x;
        }
        else {
            *status = STATUS_OK;
            node_t *elim = stack->head;
            int x = elim->data;
            stack->head->next->prev = NULL;
            stack->head = stack->head->next;
            stack->len --;
            free(elim);
            return x;
        }
    return 0;
}

int top(stack_t *stack, int *status) {
    /*
     * TODO
     *      RETURNS THE VALUE FROM THE TOP OF THE STACK
     *          - if stack is empty set status to STATUS_ERR (1)
     *          - else, set status to STATUS_OK (0)
     */
    if(stack->len == 0)
        *status = STATUS_ERR;
    else {
        *status = STATUS_OK;
        return stack->head->data;
    }
    return 0;
}
