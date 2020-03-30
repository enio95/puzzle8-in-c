#include "hashTable.h"

#ifndef ERROR
#include "errorMessage.c"
#endif

#ifndef LIST
#include "list.c"
#endif

hash *newHash()
{
  hash *h = (hash *)malloc(sizeof(hash));

  h->arr = (tnode *)malloc(tableMaxSize * sizeof(tnode));
  
  if ( h==NULL )
    errorMessageMem("newHash");

  return h;
}

void insertHash(hash *h, int v)
{
  int index = hashIndex(v);
  
  if ( h->arr[index].l == NULL )
    h->arr[index].l = newList();

  enqueue(h->arr[index].l, v);
}

void removeHash(hash *h, int v)
{
  int index = hashIndex(v);

  if ( h->arr[index].l == NULL )
    return;

  removeValue(h->arr[index].l, v);  
}

int searchHash(hash *h, int v)
{
  int index = hashIndex(v);

  if ( h->arr[index].l == NULL )
    return 0;

  return searchList(h->arr[index].l, v);
}

int hashIndex(int i) { return i%tableMaxSize; }

void printHash(hash *h)
{
  for( int i=0; i<tableMaxSize; i++ )
    if ( h->arr[i].l != NULL )
      {
	printf("Index %d\n", i);
	printList(h->arr[i].l);
      }
}
