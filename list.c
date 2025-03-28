#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List *lista = (List*) malloc(sizeof(List));
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    return lista;
}

void * firstList(List * list) {
    if(list->head == NULL) return NULL;
    list->current = list->head;
    return list->head->data;
}

void * nextList(List * list) {
    if (list->current == NULL) return NULL;
    if(list->current->next != NULL){
        list->current = list->current->next;
        return list->current->data;    
    } 
    return NULL;
}

void * lastList(List * list) {
    if(list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list->current == NULL) return NULL;
    if(list->current->prev != NULL){
        list->current = list->current->prev;
        return list->current->data;    
    }
    return NULL;
}

void pushFront(List * list, void * data) {
    Node * new = createNode(data);
    if (list->head == NULL){
        list->head = new;
        list->current = new;
        list->tail = new;
    }
    else{
        list->head->prev = new;
        new->next = list->head;
        list->head = new;
    }
}

void pushBack(List * list, void * data) {
    Node * new = createNode(data);
    if(list->head == NULL){
        list->head = new;
        list->current = new;
        list->tail = new;
    }
    else {
        list->tail->next = new;
        new->prev = list->tail;
        list->tail = new;
    }
}

void pushCurrent(List * list, void * data) {
    Node * new = createNode(data);
    if (list->head == NULL){
        list->head = new;
        list->current = new;
        list->tail = new;
    }
    else if (list->current == list->head){
        new->prev = list->current;
        list->current->next = new;
    }
    else if (list->current == list->tail){
        list->tail->next = new;
        new->prev = list->tail;
        list->tail = new;
    }
    else{
        new->next = list->current->next;
        new->prev = list->current;
        list->current->next->prev = new;
        list->current->next = new;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list->head == NULL) return NULL;
    void * data = list->current->data;
    if (list->current == list->head){
        list->head = list->head->next;
        list->current = list->head->next;
        list->head->prev = NULL;
    }
    else if (list->current == list->tail){
        list->tail = list->tail->prev;
        list->current = list->tail->prev;
        list->tail->next = NULL;
    }
    else{
        Node * izq = list->current->prev;
        Node * der = list->current->next;
        izq->next = der;
        der->prev = izq;
        list->current = der;
    }
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}