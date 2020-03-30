#ifndef HEAP
#define HEAP

#ifndef ERROR
#include "errorMessage.c"
#endif

#include <stdio.h>
#include <stdlib.h>


/*----------------------------------------------------------------
  --------------------------Made by Énio--------------------------
  -----------------------Last change 28/3/20----------------------*/

typedef struct
{
  int key;

  int vert;
  
}hnode;

typedef struct heap
{
  int size, maxSize;
  
  hnode *arr;

  int memSize, memMaxSize;

  int *mem;
  
} heap;
  

/*----------------------------Compare----------------------------*/
int compareKey(hnode *, hnode *);

/*----------------------------newHeap----------------------------*/
heap *newHeap();

/*-----------------------------Insert-----------------------------*/
void insertInHeap(heap *, int, int);

/*-----------------------------change----------------------------*/
void changeValue(heap *, int, int);

/*----------------------------extract----------------------------*/
int extractFromHeap(heap *);

/*------------------------Memory management------------------------*/
void moreMemory(heap *);

void destroyHeap(heap *);

/*------------------------------Sort------------------------------*/
void sort(heap *, int);
void sortDown(heap *, int);
void sortUp(heap *, int);
void swap(heap *, int, int);
int heapIsEmpty(heap *);

/*---------------------------print heap---------------------------*/
void printHeap(heap *);
void printSize(heap *);
void auxPrint(heap *, int, int);

/*-------------------------Non related func-------------------------*/
int power(int b, int exp);


#endif
