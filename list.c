#include "list.h"

list *newList()
{
  list *l = (list*)malloc(sizeof(list));

  if ( l==NULL )
    errorMessageMem("initiateList");

  l->size = 0;
  
  l->first = newNode(NULL);
  l->last = newNode(NULL);
  
  l->first->next = l->last;
  l->first->prev = NULL;
  
  l->last->prev = l->first;
  l->last->next = NULL;
  
  return l;
}

lnode *newNode(obj *a)
{
  lnode *n = (lnode*)malloc(sizeof(lnode));

  if ( n==NULL )
    errorMessageMem("newNode");
  
  n->prev = NULL;
  n->next = NULL;

  n->objeto =  a;

  return n;
}

void insertFirst(list *l, obj *n)
{
  lnode *temp = newNode(n);
  
  temp->prev = l->first;
  temp->next = l->first->next;

  l->first->next->prev = temp;
  l->first->next = temp;

  l->size++;
}

void push(list *l, obj *n) { insertFirst(l, n); }


void insertLast(list *l, obj *n)
{
  lnode *temp = newNode(n);
  
  temp->next = l->last;
  temp->prev = l->last->prev;

  l->last->prev->next = temp;
  l->last->prev = temp;

  l->size++;
}

void enqueue(list *l, obj *n) { insertLast(l, n); }


obj *removeFirst(list *l)
{
  if ( !l->size )
    return NULL;

  lnode *temp = l->first->next;

  if ( temp==l->last )
    errorMessageMem("removeFirst");
  
  temp->next->prev = l->first;
  l->first->next = temp->next;

  l->size--;

  return temp->objeto;
}

obj *pop(list *l) { return removeFirst(l); }

obj *dequeue(list *l) { return removeFirst(l); }


obj *removeLast(list *l)
{
  if ( !l->size )
    return NULL;

  lnode *temp = l->last->prev;

  if ( temp==l->first )
    errorMessageMem("removeLast");
  
  temp->prev->next = l->last;
  l->last->prev = temp->prev;

  l->size--;

  return temp->objeto;
}

int listSize(list *l)
{
  if ( l->size<0 )
    errorMessageIllegalSize("listSize");
  
  return l->size;
};

int isEmpty(list *l ) { return l->size ? 0: 1; }


obj *getFirst(list *l)
{
  if ( isEmpty(l) )
    return NULL;

  return l->first->next->objeto;
}

obj *top(list *l) { return getFirst(l); }


obj *getLast(list *l)
{
  if ( isEmpty(l) )
    return NULL;

  return l->last->prev->objeto;
}

void printList(list *l)
{
  printf("List size = %d\n", l->size);

  printf("Its Members are\n");

  if ( isEmpty(l) )
    printf("None\n");

  else
    {
      int i=0;
      
      for( lnode *cur = l->first->next; cur!=l->last; cur = cur->next )
	{
	  printf("Index = %d\n", i++);
	  printObject(cur->objeto);
	}
    }
}

void errorMessageIllegalSize(char *str)
{
  fprintf(stderr, "List size is Lower than 0, error on %s", str);
  exit(EXIT_FAILURE);
}

void errorMessageListSize(char *str)
{
  fprintf(stderr, "List size does not match its contents, error on %s", str);
  exit(EXIT_FAILURE);
}
