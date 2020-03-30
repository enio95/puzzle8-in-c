#include "objeto.h"

//Don't forget to define how to create your object
obj *newObject(char *arr, obj *father)
{
  obj *new = (obj*)malloc(sizeof(obj));

  if ( new==NULL )
    errorMessageMem("newObject");

  new->pattern = arr;

  new->father = father;

  if ( father!=NULL )
    new->g = father->g + 1;

  else
    new->g = 0;
  
  return new;
}

/*Don't forget to define how to compare your object
  Return types:
  0  -> Means a==b
  >0 -> Means a>b
  <0 -> Means a<b */
int compare(obj *a, obj *b)
{
  for( int i=0; i<9; i++ )
    if ( a->pattern[i]!=b->pattern[i] )
      return a->pattern[i] - b->pattern[i];

  return 0;
}

/*Don't forget to define how to print your object */
void printObject(obj *a)
{
  printf("\n");
  for( int i=0; i<3; putchar('\n'), i++ )
    for( int j=0; j<3; printf("%c ", a->pattern[i*3+j]), j++ );

  putchar('\n');
}

/* Error message, shall be left unchanged*/
void errorMessageMem(char *str)
{
  fprintf(stderr, "Memory allocation failed in %s\n", str);
  exit(EXIT_FAILURE);
}
