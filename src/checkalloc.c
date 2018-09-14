#include <stdio.h>
#include <stdlib.h>

#include "checkalloc.h"

// Check Memory Allocation
void check_alloc_spec(const void *ptr, const char *caller)
{
  if(!ptr)
  {
    fprintf(stderr, "Error allocating memory in %s()\n", caller);
    abort();
  }
}
