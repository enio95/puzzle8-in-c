#include <stdio.h>
#include <stdlib.h>
#include "list.c"
#include "objeto.c"
#include "heap.c"

obj *start, *goal;

#define MAXSIZE 362880 // 9!
int size;

/*---------------------------Read---------------------------------*/
void readInput();
void readArray(char *);

/*-----------------------Initiate Memory---------------------------*/
char **initiateMemory();
obj *initiateMemory1();

/*-----------------------new Combination-------------------------*/
char * newComb(char *, int, char);
void movePoint(int *, int *, char);
int validPoint(int, int);
char *copy(char *);
void swapPoint(char *, int, int);
void rotateDir(char *);

/*---------------------------Search-----------------------------*/
int findBlank(char *);
int search(char **, char *);
int search1(obj *, char *);
int equalArray(char *, char *);

/*--------------------------Print------------------------------*/
void printPath(obj *);

/*-----------------------------BFS---------------------------------*/
obj *bfs();

/*-----------------------------DFS---------------------------------*/
obj *dfs();

/*---------------------------Best First----------------------------*/
obj *bestFirst();
int dif(char *, char *);

/*----------------------------aStar-------------------------------*/
obj *aStar();

int main()
{
  //printPath(bfs());
  //printPath(dfs());
  //printPath(bestFirst());
  //printPath(aStar());
  
  return 0;
}
/*---------------------------Read---------------------------------*/
void readInput()
{
  char *arr = (char *)malloc(9*sizeof(char));
  char *vec = (char *)malloc(9*sizeof(char));

  readArray(arr);
  readArray(vec);

  start = newObject(arr, NULL); goal = newObject(vec, NULL);

  if ( start==NULL || goal==NULL )
    errorMessageMem("readInput");
}

void readArray(char *arr)
{
  for( int i=0; i<9; i++ )
    {
      arr[i] = getchar();
      getchar();
    }  
}

/*-----------------------Initiate Memory---------------------------*/
char **initiateMemory()
{
  char **memory = (char **)malloc(MAXSIZE * sizeof(char *));

  if ( memory==NULL )
    errorMessageMem("initiateMemory");

  memory[0] = start->pattern;
  size = 1;

  return memory;
}

obj *initiateMemory1()
{
  obj *memory = (obj *)malloc(MAXSIZE * sizeof(obj));

  if ( memory==NULL )
    errorMessageMem("initiateMemory1");

  memory[0].pattern = start->pattern;
  memory[0].father = NULL;
  memory[0].g = 0;
  
  size = 1;

  return memory;
}

/*-------------------------new Combination-------------------------*/
char *newComb(char *arr, int ref, char dir)
{
  int l = ref/3, c = ref%3;

  movePoint(&l, &c, dir);

  if ( !validPoint(l, c) )
    return NULL;

  char *vec = copy(arr);
  
  swapPoint(vec, ref, l*3+c);

  return vec;
}

void movePoint(int *l, int *c, char dir)
{
  switch( dir )
    {
    case 'e':
      (*c)++;
      break;

    case 'w':
      (*c)--;
      break;

    case 'n':
      (*l)--;
      break;

    default:
      (*l)++;
      break;
    }
}

int validPoint(int l, int c)
{
  return c<0 || l<0 || c>=3 || l>=3 ? 0: 1;
}

char *copy(char *arr)
{
  char *vec = (char *)malloc(9*sizeof(char));

  if ( vec==NULL )
    errorMessageMem("copy");
  
  for( int i=0; i<9; vec[i]=arr[i], i++ );

  return vec;
}

void swapPoint(char *arr, int p1, int p2)
{
  char temp = arr[p1];

  arr[p1] = arr[p2];
  arr[p2] = temp;
}

void rotateDir(char *dir)
{
  switch( *dir )
    {
    case 'e':
      *dir = 'n';
      break;

    case 'n':
      *dir = 'w';
      break;

    case 'w':
      *dir = 's';
      break;

    default:
      *dir = 'e';
      break;
    }
}

/*------------------------------Search-----------------------------*/
int findBlank(char *arr)
{
  int i;
  
  for( i=0; i<9 && arr[i]!='0'; i++ );

  return i;
}

int search(char **memory, char *arr)
{
  for( int i=0; i<size; i++ )
    if ( equalArray(memory[i], arr) )
      return 1;

  return 0;
}

int search1(obj *memory, char *arr)
{
  int i;
  
  for( i=0; i<size && !equalArray(memory[i].pattern, arr); i++);

  return i!=size ?1: 0;
}

int equalArray(char *arr, char *vec)
{
  for( int i=0; i<9; i++ )
    if ( arr[i]!=vec[i] )
      return 0;

  return 1;
}

/*--------------------------Print------------------------------*/
void printPath(obj *n)
{
  list *s = newList();

  for ( obj *cur = n; cur!=NULL; cur = cur->father )
    push(s, cur);

  printList(s);
}

/*-----------------------------DFS---------------------------------*/
obj *bfs()
{
  readInput();
  printObject(start); printObject(goal);

  char **memory = initiateMemory();
  
  list *l = newList();
  enqueue(l, start);

  int ref;
  obj *cur;
  char dir, *arr;
  
  do
    {
      cur = dequeue(l);
      
      ref = findBlank(cur->pattern);

      for( int i=0; i<4; rotateDir(&dir), i++ )
	{
	  arr = newComb(cur->pattern, ref, dir);

	  if ( arr!=NULL && !search(memory, arr) )
	    {
	      memory[size] = arr;
	      size++;

	      enqueue(l, newObject(arr, cur));
	    }

	  else if ( arr!=NULL )
	    free(arr);
	}
      
    } while ( !equalArray(cur->pattern, goal->pattern) && !isEmpty(l) );

  return cur;
}

/*-----------------------------DFS---------------------------------*/
obj *dfs()
{
  readInput();
  printObject(start); printObject(goal);

  char **memory = initiateMemory();
  
  list *l = newList();
  push(l, start);

  
  int ref;
  obj *cur;
  char dir, *arr;

  do
    {
      cur = pop(l);

      ref = findBlank(cur->pattern);
    
      for( int i=0; i<4; rotateDir(&dir), i++ )
	{
	  arr = newComb(cur->pattern, ref, dir);
	  
  	  if ( arr!=NULL && !search(memory, arr) )
	    {
	      memory[size] = arr;
	      size++;

	      push(l, newObject(arr, cur));
	    }
	  
	  else if ( arr!=NULL )
	    free(arr);
	}
    } while ( !equalArray(cur->pattern, goal->pattern) && !isEmpty(l) );

  return cur;     
}

/*---------------------------Best First----------------------------*/
obj *bestFirst()
{
  readInput();
  printObject(start); printObject(goal);
  
  obj *memory = initiateMemory1();
  
  heap *h = newHeap();
  insertInHeap(h, 0, dif(start->pattern, goal->pattern));
  
  int ref, index;
  char dir, *arr;

  do
    {
      index = extractFromHeap(h);

      ref = findBlank(memory[index].pattern);

      for( int i=0; i<4; rotateDir(&dir), i++ )
	{
	  arr = newComb(memory[index].pattern, ref, dir);

	  if ( arr!=NULL && !search1(memory, arr) )
	    {
	      memory[size].pattern = arr;
	      memory[size].father = &memory[index];
	      
	      insertInHeap(h, size, dif(arr, goal->pattern));

	      size++;
	    }
	  
	  else if ( arr!=NULL )
	    free(arr);
	}
      
    }while( !equalArray(goal->pattern, memory[index].pattern) && !heapIsEmpty(h) );

  return &memory[index];  
}

int dif(char *arr, char *vec)
{
  int n=0;

  for( int i=0; i<9; i++ )
    if ( arr[i]!=vec[i] )
      n++;

  return n;
}

/*----------------------------aStar-------------------------------*/
obj *aStar()
{
  readInput();
  printObject(start); printObject(goal);
  
  obj *memory = initiateMemory1();
  
  heap *h = newHeap();
  insertInHeap(h, 0, dif(start->pattern, goal->pattern));
  
  int ref, index;
  char dir, *arr;

  do
    {
      index = extractFromHeap(h);

      ref = findBlank(memory[index].pattern);

      for( int i=0; i<4; rotateDir(&dir), i++ )
	{
	  arr = newComb(memory[index].pattern, ref, dir);

	  if ( arr!=NULL && !search1(memory, arr) )
	    {
	      memory[size].pattern = arr;
	      memory[size].father = &memory[index];
	      memory[size].g = memory[index].g + 1;
	      
	      insertInHeap(h, size, dif(arr, goal->pattern) + memory[size].g);

	      size++;
	    }
	  
	  else if ( arr!=NULL )
	    free(arr);
	}
      
    }while( !equalArray(goal->pattern, memory[index].pattern) && !heapIsEmpty(h) );

  return &memory[index];  
}
