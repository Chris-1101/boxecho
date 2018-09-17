#include <stdio.h>
#include <string.h>

#include "strtrm.h"

// Trim Character From String Start/End
char *strtrm(char *str, const char chr)
{
  if (str == NULL)
  {
    return NULL;
  }

  size_t len_str = strlen(str);

  while(len_str > 0 && str[0] == chr)
  {
    str++;
    len_str--;
  }

  while(len_str > 0 && str[len_str - 1] == chr)
  {
    str[--len_str] = '\0';
  }

  return str;
}
