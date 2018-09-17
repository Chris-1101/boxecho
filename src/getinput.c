#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "getinput.h"
#include "checkalloc.h"

void get_input(int argc, char **argv, char *res)
{
  char *str;

  if (isatty(fileno(stdin)))
  {
    if (argc > 1)
    {
      for (size_t i = 1; i < argc; i++)
      {
        if (i == 1)
        {
          str = malloc((strlen(argv[i]) + 1 + 1) * sizeof(*str));
          check_alloc(str);
          strcpy(str, argv[i]);
        }
        else
        {
          str = realloc(str, strlen(str) + strlen(argv[i]) + 1 + 1);
          check_alloc(str);
          strcat(str, argv[i]);
        }
        strcat(str, " ");
      }
    }
    else
    {
      str = strdup("");
      check_alloc(str);
    }
  }
  else
  {
    char buffer[BUFSIZ];
    int buffer_size = BUFSIZ - 1;
    size_t c = 0;

    while(fgets(buffer, buffer_size, stdin))
    {
      if (c == 0)
      {
        str = malloc((strlen(buffer) + 1) * sizeof(*str));
        check_alloc(str);
        strcpy(str, buffer);
      }
      else
      {
        str = realloc(str, strlen(str) + strlen(buffer) + 1);
        check_alloc(str);
        strcat(str, buffer);
      }
      c++;
    }
  }
  size_t len_str = strlen(str);

  while(len_str > 0 && str[len_str - 1] == '\n')
  {
    str[--len_str] = '\0';
  }

  memcpy(res, str, strlen(str) + 1);
  free(str);
}
