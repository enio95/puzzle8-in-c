#ifndef LIST
#define LIST

#include "objeto.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct lnode
{
  struct obj *objeto;

  struct lnode *prev, *next;
  
}lnode;

typedef struct
{
  int size;

  struct lnode *first, *last;
  
}list;


list *newList();

lnode *newNode(obj *);

void insertFirst(list *, obj *);
void push(list *, obj *);

void insertLast(list *, obj *);
void enqueue(list *, obj *);

obj *removeFirst(list *);
obj *pop(list *);
obj *dequeue(list *);

obj *removeLast(list *);

int listSize(list *);
int isEmpty(list *);

obj *getFirst(list *);
obj *top(list *);

obj *getLast(list *);

void errorMessageIllegalSize(char *);
void errorMessageListSize(char *);

#endif
