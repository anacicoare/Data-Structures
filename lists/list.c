#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

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

void destroy_list(list_t* list) {
    node_t* aux;

    while (list->len > 0) {
        aux = list->tail;                   
        list->tail = list->tail->prev;      
        free_node(aux);                
        --list->len;                        
    }

    free(list);
}

void print_list(list_t* list) {
    node_t* aux = list->head;

    printf("%-25s", "Lista construita (->):");

    if (aux == NULL) {
        // empty list
        printf("NULL\n");
        return;
    }

    while (aux != list->tail) {
        printf("%d -> ", *aux->data);
        aux = aux->next;
    }
    printf("%d\n", *aux->data);
}

int insert_node(list_t* list, int value, int position) {
    int i;

    if (position < 0 || position > list->len)
    {
        printf("Position not in range.\n");
        return -1;
    }

    node_t* nod = init_node(&value);

    if (list->len == 0)
    {
        list->head = nod;
        list->tail = nod;
        list->len = 1;
        return 0;
    }

    if (position == 0)
    {
        nod->prev = NULL;
        nod->next = list->head;
        list->head->prev = nod;
        list->head = nod;
        list->len++;
        return 0;
    }

    if (position == list->len)
    {
        nod->next = NULL;
        nod->prev = list->tail;
        list->tail->next = nod;
        list->tail = nod;
        list->len++;
        return 0;
    }

    if (position < list->len / 2 && position != 0)
    {
        node_t* next = list->head;
        for (i = 0; i < position; i++)
            next = next->next;
        node_t* first = next->prev;
        nod->next = next;
        nod->prev = first;
        next->prev = nod;
        first->next = nod;
        list->len++;
        return 0;
    }

    if (position > list->len / 2 && position != list->len)
    {
        node_t* next = list->tail;
        for (i = list->len; i > position+1; i--)
            next = next->prev;
        node_t* first = next->prev;
        nod->next = next;
        nod->prev = first;
        next->prev = nod;
        first->next = nod;
        list->len++;
        return 0;
    }

    return 0;
}

int remove_node(list_t* list, int position) {

    if (position < 0 || position > list->len)
    {
        printf("Position not in list\n");
            return -1;
    }
    node_t* elim_nod;

    //beginning of the list
    if (position == 0)
    {
        elim_nod = list->head;
        elim_nod->next->prev = NULL;
        list->head = elim_nod->next;
        list->len--;
        free_node(elim_nod);
        return 0;
    }
    
    //end of list
    if (position == list->len)
    {
        elim_nod = list->tail;
        elim_nod->prev->next = NULL;
        list->tail = elim_nod->prev;
        list->len--;
        free_node(elim_nod);
        return 0;
    }

    //first half
    if (position < list->len / 2)
    {
        elim_nod = list->head;
        for (int i = 0; i < position; i++)
            elim_nod = elim_nod->next;
        node_t* first, * last;
        first = elim_nod->prev;
        last = elim_nod->next;
        first->next = last;
        last->prev = first;
        free_node(elim_nod);
        list->len--;
        return 0;
    }

    //second half
    if (position >= list->len / 2)
    {
        elim_nod = list->tail;
        for (int i = list->len; i > position + 1; i--)
            elim_nod = elim_nod->prev;
        node_t* first, * last;
        first = elim_nod->prev;
        last = elim_nod->next;
        first->next = last;
        last->prev = first;
        free_node(elim_nod);
        list->len--;
        return 0;
    }

    return -2;
}
