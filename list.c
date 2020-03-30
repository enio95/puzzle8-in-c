#include "list.h"
#define INVALID 2147483648


list *newList()
{
  list *l = (list*)malloc(sizeof(list));

  if ( l==NULL )
    errorMessageMem("initiateList");

  l->size = 0;
  
  l->first = newNode(INVALID);
  l->last = newNode(INVALID);
  
  l->first->next = l->last;
  l->first->prev = NULL;
  
  l->last->prev = l->first;
  l->last->next = NULL;
  
  return l;
}

lnode *newNode(int a)
{
  lnode *n = (lnode*)malloc(sizeof(lnode));

  if ( n==NULL )
    errorMessageMem("newNode");
  
  n->prev = NULL;
  n->next = NULL;

  n->value =  a;

  return n;
}

void insertFirst(list *l, int n)
{
  lnode *temp = newNode(n);
  
  temp->prev = l->first;
  temp->next = l->first->next;

  l->first->next->prev = temp;
  l->first->next = temp;

  l->size++;
}

void push(list *l, int n) { insertFirst(l, n); }


void insertLast(list *l, int n)
{
  lnode *temp = newNode(n);
  
  temp->next = l->last;
  temp->prev = l->last->prev;

  l->last->prev->next = temp;
  l->last->prev = temp;

  l->size++;
}

void enqueue(list *l, int n) { insertLast(l, n); }


int removeFirst(list *l)
{
  if ( !l->size )
    return INVALID;

  lnode *temp = l->first->next;

  if ( temp==l->last )
    errorMessageMem("removeFirst");
  
  temp->next->prev = l->first;
  l->first->next = temp->next;

  l->size--;

  return temp->value;
}

int pop(list *l) { return removeFirst(l); }

int dequeue(list *l) { return removeFirst(l); }


int removeLast(list *l)
{
  if ( !l->size )
    return INVALID;

  lnode *temp = l->last->prev;

  if ( temp==l->first )
    errorMessageMem("removeLast");
  
  temp->prev->next = l->last;
  l->last->prev = temp->prev;

  l->size--;

  return temp->value;
}

void removeValue(list *l, int v)
{
  lnode *cur;
  
  for( cur = l->first->next; cur!=l->last && cur->value!=v; cur = cur->next );

  if ( cur==l->last )
    return;

  cur->next->prev = cur->prev;
  cur->prev->next = cur->next;

  l->size--;
}

int listSize(list *l)
{
  if ( l->size<0 )
    errorMessageIllegalSize("listSize");
  
  return l->size;
};

int isEmpty(list *l ) { return l->size ? 0: 1; }


int getFirst(list *l)
{
  if ( isEmpty(l) )
    return INVALID;

  return l->first->next->value;
}

int top(list *l) { return getFirst(l); }


int getLast(list *l)
{
  if ( isEmpty(l) )
    return INVALID;

  return l->last->prev->value;
}

int searchList(list *l, int v)
{
  for( lnode *cur = l->first->next; cur!=l->last; cur = cur->next )
    if ( cur->value == v )
      return 1;

  return 0;
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
	  printf("Value = %d\n", cur->value);
	}
    }
}
