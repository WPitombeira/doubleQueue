//
// Created by root on 17/09/2019.
//

#ifndef FILAORDENADA_FILAORDENADA_H
#define FILAORDENADA_FILAORDENADA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct  {
    int key;
//    char *name;
} Object;

typedef struct NodeList *Pointer;

typedef struct NodeList {
    Object element;
    Pointer next;
    Pointer prev;
} NodeList;

typedef struct {
    Pointer first;
    Pointer last;
    int size;
} List;

void initList(List *list);
void insert(List *list, Object x);
void printList(List *list);
void printReverse(List *list);
void destroyList(List *list);
bool isEmpty(List *list);
bool search(List *list, int key);
int size(List *list);
void removeElement(List *list, int key, Object *item);
void removeFirst(List *list, Object *item);
void removeLast(List *list, Object *item);
Object first(List *list);
Object last(List *list);
bool write(FILE *arq, List *list, char mode);

#endif //FILAORDENADA_FILAORDENADA_H
