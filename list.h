#ifndef LIST
#define LIST

#ifndef ERROR
#include "errorMessage.c"
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct lnode
{
  int value;

  struct lnode *prev, *next;
  
}lnode;

typedef struct
{
  int size;

  struct lnode *first, *last;
  
}list;


list *newList();

lnode *newNode(int);

void insertFirst(list *, int);
void push(list *, int);

void insertLast(list *, int);
void enqueue(list *, int);

int removeFirst(list *);
int pop(list *);
int dequeue(list *);

int removeLast(list *);

void removeValue(list *, int);

int listSize(list *);
int isEmpty(list *);

int getFirst(list *);
int top(list *);
int searchList(list *, int);

int getLast(list *);

#endif
