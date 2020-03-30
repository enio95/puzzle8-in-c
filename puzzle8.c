#include <stdio.h>
#include <stdlib.h>
#include "heap.c"
#include "list.c"
#include "hashTable.c"

#define MAXSIZE 362880 // 9!

/*----------------------Memory structure-------------------------*/
typedef struct mem
{
  char *pattern;

  int g;

  struct mem *father;
  
}mem;

/*----------------------Global variables---------------------------*/
char *start, *goal;
int memIndex;

/*---------------------------Read----------------------------------*/
void readInput();
void readArray(char *);

/*---------------------------Print---------------------------------*/
void printArray(char *);
void printPath(mem *, mem *);

/*-----------------------Initiate Memory---------------------------*/
mem *initiateMemory(hash *);

/*-----------------------new Combination---------------------------*/
char * newComb(char *, int, char);

char *copy(char *);
void swapPoint(char *, int, int);

void movePoint(int *, int *, char);
int validPoint(int, int);

void rotateDir(char *);

/*-----------------------------BFS---------------------------------*/
mem *bfs(mem *, hash *);

/*-----------------------------DFS---------------------------------*/
mem *dfs(mem *, hash *);

/*--------------------------BestFirst------------------------------*/
mem *bestFirst(mem *, hash *);
int dif(char *, char *);

/*-----------------------------A*------------------------------*/
mem *aStar(mem *, hash *);

/*--------------------------Find/Equal-----------------------------*/
int findBlank(char *);
int equalPattern(char *, char *);



int main()
{
  readInput();
  printArray(start); printArray(goal);

  hash *t = newHash();
  
  mem *memory = initiateMemory(t);

  //printPath(memory, bfs(memory, t));
  //printPath(memory, dfs(memory, t));
  //printPath(memory, bestFirst(memory, t));
  printPath(memory, aStar(memory, t));
  
  return 0;
}

/*---------------------------Read---------------------------------*/
void readInput()
{
  goal = (char *)malloc(9*sizeof(char));
  start = (char *)malloc(9*sizeof(char));
  
  if ( start==NULL || goal==NULL )
    errorMessageMem("readInput");
  
  readArray(start);
  readArray(goal);
}

void readArray(char *arr)
{
  for( int i=0; i<9; i++ )
    {
      arr[i] = getchar();
      getchar();
    }  
}

/*--------------------------Print------------------------------*/
void printArray(char *arr)
{
  for( int i=0; i<3; putchar('\n'), i++ )
    for( int j=0; j<3; printf("%c ", arr[i*3 + j]), j++ );

  putchar('\n');
}

void printPath(mem *memory, mem *value)
{
  list *s = newList();

  for( mem *cur = value; cur!=NULL; cur = cur->father )
    push(s, (int)(cur - memory) );
  
  int i=0;
  
  while ( !isEmpty(s) )
    {
      printf("Passo %d:\n", i++);
      printArray(memory[pop(s)].pattern);
    }
}

/*-----------------------Initiate Memory---------------------------*/
mem *initiateMemory(hash *t)
{
  mem *memory = (mem *)malloc(MAXSIZE * sizeof(mem));

  if ( memory == NULL )
    errorMessageMem("initiateMemory");

  memory[0].pattern = start;
  memory[0].father = NULL;
  memory[0].g = 0;
  memIndex = 1;
  
  insertHash(t, atoi(start));

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

/*-----------------------------BFS---------------------------------*/
mem *bfs(mem *memory, hash *t)
{
  list *l = newList();
  enqueue(l, 0);

  int blank, ind;
  char dir, *pattern;

  do
    {
      ind = dequeue(l);

      blank = findBlank(memory[ind].pattern);

      for( int i=0; i<4; rotateDir(&dir), i++ )
	{
	  pattern = newComb(memory[ind].pattern, blank, dir);

	  if ( pattern!=NULL && !searchHash(t, atoi(pattern)) )
	    {
	      memory[memIndex].pattern = pattern;
	      memory[memIndex].father = &memory[ind];
	      
	      if ( equalPattern(pattern, goal) )
		return &memory[memIndex];

	      else
		{
		  insertHash(t, atoi(pattern));
		  enqueue(l, memIndex);
		  memIndex++;
		}
	    }

	  else
	    free(pattern);
	}
      
    } while ( !equalPattern(memory[ind].pattern, goal) && !isEmpty(l) );

  free(l);
  
  return &memory[ind];
}

/*-----------------------------DFS---------------------------------*/
mem *dfs(mem *memory, hash *t)
{
  list *l = newList();
  push(l, 0);

  int blank, ind;
  char dir, *pattern;

  do
    {
      ind = pop(l);

      blank = findBlank(memory[ind].pattern);

      for( int i=0; i<4; rotateDir(&dir), i++ )
	{
	  pattern = newComb(memory[ind].pattern, blank, dir);

	  if ( pattern!=NULL && !searchHash(t, atoi(pattern)) )
	    {
	      memory[memIndex].pattern = pattern;
	      memory[memIndex].father = &memory[ind];
	      
	      if ( equalPattern(pattern, goal) )
		return &memory[memIndex];

	      else
		{
		  insertHash(t, atoi(pattern));
		  push(l, memIndex);
		  memIndex++;
		}
	    }

	  else
	    free(pattern);
	}
      
    } while ( !equalPattern(memory[ind].pattern, goal) && !isEmpty(l) );

  free(l);
  
  return &memory[ind];
}

/*--------------------------BestFirst------------------------------*/
mem *bestFirst(mem *memory, hash *t)
{
  heap *h = newHeap();
  insertInHeap(h, 0, dif(start, goal));

  int blank, ind;
  char dir, *pattern;

  do
    {
      ind = extractFromHeap(h);

      blank = findBlank(memory[ind].pattern);

      for( int i=0; i<4; rotateDir(&dir), i++ )
	{
	  pattern = newComb(memory[ind].pattern, blank, dir);

	  if ( pattern!=NULL && !searchHash(t, atoi(pattern)) )
	    {
	      memory[memIndex].pattern = pattern;
	      memory[memIndex].father = &memory[ind];
	      
	      if ( equalPattern(pattern, goal) )
		return &memory[memIndex];

	      else
		{
		  insertHash(t, atoi(pattern));
		  insertInHeap(h, memIndex, dif(pattern, goal));
		  memIndex++;
		}	      
	    }
	  else
	    free(pattern);
	}
    }while ( !equalPattern(memory[ind].pattern, goal) && !heapIsEmpty(h) );

  return &memory[ind];
}


int dif(char *arr, char *vec)
{
  int n=0;

  for( int i=0; i<9; i++ )
    if ( arr[i]!=vec[i] )
      n++;

  return n;
}
  
/*-----------------------------A*------------------------------*/
mem *aStar(mem *memory, hash *t)
{
  heap *h = newHeap();
  insertInHeap(h, 0, dif(start, goal));

  int blank, ind;
  char dir, *pattern;

  do
    {
      ind = extractFromHeap(h);

      blank = findBlank(memory[ind].pattern);

      for( int i=0; i<4; rotateDir(&dir), i++ )
	{
	  pattern = newComb(memory[ind].pattern, blank, dir);

	  if ( pattern!=NULL && !searchHash(t, atoi(pattern)) )
	    {
	      memory[memIndex].pattern = pattern;
	      memory[memIndex].father = &memory[ind];
	      memory[memIndex].g = memory[ind].g + 1;
	      
	      if ( equalPattern(pattern, goal) )
		return &memory[memIndex];

	      else
		{
		  insertHash(t, atoi(pattern));
		  insertInHeap(h, memIndex, dif(pattern, goal) + memory[memIndex].g);
		  memIndex++;
		}	      
	    }
	  else
	    free(pattern);
	}
    }while ( !equalPattern(memory[ind].pattern, goal) && !heapIsEmpty(h) );

  return &memory[ind];
}


/*--------------------------Find/Equal-----------------------------*/
int findBlank(char *arr)
{
  int i;
  
  for( i=0; i<9 && arr[i]!='0'; i++ );

  return i;
}

int equalPattern(char *p1, char *p2)
{
  for( int i=0; i<9; i++ )
    if ( p1[i] != p2[i] )
      return 0;

  return 1;
}
