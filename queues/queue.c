#include <stdio.h>
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

list_t* init_list() {
    list_t* new_list = malloc(sizeof(list_t));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->len = 0;

    return new_list;
}

void free_node(node_t* nod)
{
    free(nod->data);
    free(nod);
}

typedef list_t queue_t;

void enqueue(queue_t *queue, int value) {
    /*
     * TODO
     *      ADD NEW ELEMENT IN QUEUE
     *      - if there are no elements in queue set head and tail as being the new node
     *      - otherwise, put new node as first element
     */
    node_t *new = initNode(value);
    if(queue->len == 0) {
        queue->head = queue->tail = new;
    }
    else {
        new->next = queue->head;
        queue->head->prev = new;
        queue->head = new;
    }
    queue->len ++;
}

int dequeue(queue_t *queue, int *status) {
    /*
     * TODO
     *      ERASE LAST ELEMENT FROM THE END OF THE QUEUE
     *      - IF there are no elements in the queue:
     *          - set status on STATUS_ERR (1)
     *          - returns something
     *      - ELSE:
     *          - copy node value
     *          - set status on STATUS_OK (0)
     *          - return node data
     */
    if(queue->len == 0) {
        *status = STATUS_ERR;
        return 0;
    }
    else 
        if(queue->len == 1) {
            node_t *elim = queue->tail;
            int x = elim->data;
            queue->head = queue->tail = NULL;
            free(elim);
            *status = STATUS_OK;
            queue->len --;
            return x;
        }
        else {
            node_t *elim = queue->tail;
            int x = elim->data;
            queue->tail->prev->next = NULL;
            queue->tail = queue->tail->prev;
            *status = STATUS_OK;
            free(elim);
            queue->len --;
            return x;
        }
}

int peek(queue_t *queue, int *status) {
    /*
     * TODO
     *      PRINT LAST ELEMENT OF THE QUEUE
     *      - IF there are no elements in the queue:
     *          - set status on STATUS_ERR (1)
     *          - return something
     *      - OTHERWISE:
     *          - set status on STATUS_OK (0)
     *          - return node data, this time without erasing the node
     */
    if(queue->len == 0) {
        *status = STATUS_ERR;
        return 0;
    }
    else {
        *status = STATUS_OK;
        return queue->tail->data;
    }
    return 0;
}
