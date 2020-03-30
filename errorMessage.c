#include "errorMessage.h"

void errorMessageMem(char *str)
{
  fprintf(stderr, "Memory allocation failed on %s", str);
  exit(EXIT_FAILURE);
  
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

void errorMessageIndex(char *str)
{
  fprintf(stderr, "you are suposed to insert the INDEX of your object. Failed on %s\n", str);
  exit(EXIT_FAILURE);    
}
