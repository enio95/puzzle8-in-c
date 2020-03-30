#include "heap.h"

/*----------------------------------------------------------------
  --------------------------Made by Énio--------------------------
  -----------------------Last change 28/3/20----------------------*/

/*----------------------------Compare----------------------------*/
/* HeapMin*/
int compareKey(hnode *a, hnode *b) { return a->key - b->key; }

/* heapMax*/
//int compareKey(hnode *a, hnode *b) { return b->key - a->key; }

/*----------------------------newHeap----------------------------*/
heap *newHeap()
{
  heap *new = (heap *)malloc(sizeof(heap));

  if ( new==NULL )
    errorMessageMem("newHeap");

  new->maxSize = 0; new->size = 0;

  new->memMaxSize = 0; new->memSize = 0;

  new->arr = NULL; new->mem = NULL;

  return new;
}

/*-----------------------------Insert-----------------------------*/
void insertInHeap(heap *h, int vert, int key)
{
  if ( vert != h->memSize )
    errorMessageIndex("insertInHeap");

  h->memSize++; h->size++;
  moreMemory(h);

  h->mem[ vert ] = h->size - 1;
  
  h->arr[ h->size - 1 ].vert = vert;
  h->arr[ h->size - 1 ].key = key;

  sortUp(h, h->size - 1);
}

/*----------------------------extract----------------------------*/
int extractFromHeap(heap *h)
{
  int temp = h->arr[0].vert;
  
  swap(h, 0, h->size-1);
  
  h->size--;
  
  sortDown(h, h->arr[0].vert);  
  
  return temp;
}

/*-----------------------------change----------------------------*/
void changeValue(heap *h, int vert, int key)
{
  if ( h->mem[vert] >= h->size )
    return;
  
  h->arr[ h->mem[vert] ].key = key;

  sort(h, vert);
}
/*------------------------------Sort------------------------------*/
void sort(heap *h, int vert)
{
  sortDown(h, vert);
  sortUp(h, vert);
}

#define left(i) ( i*2 + 1 )
#define right(i) ( i*2 + 2 )
void sortDown(heap *h, int vert)
{
  if ( vert >= h->memSize || vert < 0)
    return;

  int ind = h->mem[vert];
  
  if ( ind >= h->size )
    return;

  int l = left(ind), r = right(ind), cur = ind;

  if ( l < h->size && compareKey(&h->arr[cur], &h->arr[l]) > 0 )
    cur = l;

  if ( r < h->size && compareKey(&h->arr[cur], &h->arr[r]) > 0 )
    cur = r;

  if ( cur != ind )
    {
      swap(h, cur, ind);
      sortDown(h, h->arr[cur].vert);
    }
}

#define father(i) ( (i-1) / 2 )
void sortUp(heap *h, int vert)
{
  if ( vert >= h->memSize || vert < 0)
    return;

  int ind = h->mem[vert];
  
  if ( ind==0 || ind >= h->size )
    return;

  if ( compareKey(&h->arr[ind], &h->arr[ father(ind) ]) > 0 )
    return;

  swap(h, ind, father(ind));

  sortUp(h, h->arr[father(ind)].vert);
}

void swap(heap *h, int a, int b)
{
  h->mem[ h->arr[a].vert ] = b;
  h->mem[ h->arr[b].vert ] = a;

  hnode temp = h->arr[a];

  h->arr[a] = h->arr[b];
  h->arr[b] = temp;
}

int heapIsEmpty(heap *h) { return h->size==0 ? 1: 0; }

/*------------------------Memory management------------------------*/
void moreMemory(heap *h)
{
  if ( h->size > h->maxSize || h->maxSize==0 )
    {
      if ( h->maxSize == 0 )
	h->maxSize = 2;

      else
	h->maxSize *= 2;

      h->arr = (hnode *)realloc(h->arr, h->maxSize * sizeof(hnode));

      if ( h->arr == NULL )
	errorMessageMem("moreMemory");
    }

  if ( h->memSize > h->memMaxSize || h->memMaxSize == 0 )
    {
      if ( h->memMaxSize == 0 )
	h->memMaxSize = 2;

      else
	h->memMaxSize *= 2;

      h->mem = (int *)realloc(h->mem, h->memMaxSize * sizeof(int));

      if ( h->mem == NULL )
	errorMessageMem("moreMemory");
    }
}

void destroyHeap(heap *h)
{
  free(h->mem); free(h->arr); free(h);
}

/*---------------------------print heap---------------------------*/
void printSize(heap *h)
{ printf("HeapMaxSize = %d, heapSize = %d\n", h->maxSize, h->size); }

void printHeap(heap *h)
{
  printSize(h);
  
  auxPrint(h, 0, 0);
}

void auxPrint(heap *h, int level, int start)
{
  printf("\nLevel = %d\n", level);

  int lim = power(2, level);

  for( int i=start; i<h->size && i<start+lim; i++ )
    {
      printf("Key = %d\n", h->arr[i].key);
      printf("vert= %d\n\n", h->arr[i].vert);
    }
  
  if ( h->size>=start+lim )
    auxPrint(h, level+1, power(2, level+1) - 1);
}

/*-------------------------Non related func-------------------------*/
int power(int b, int exp)
{
  if ( exp==0 )
    return 1;

  else if ( exp==1 )
    return b;
  
  else  if ( exp%2 == 0 )
    return power(b*b, exp/2);
  
  else
    return b*power(b*b, exp/2);
}
