#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>

#include "getinput.h"
#include "checkalloc.h"

// =================================
// ------- 𝙉𝙖𝙧𝙧𝙤𝙬 𝘾𝙝𝙖𝙧𝙖𝙘𝙩𝙚𝙧 -------
// =================================
// Consolidate Input From All Sources
void get_input(int argc, char **argv, char *res)
{
  char *str;
  size_t len_space = 1;

  if (isatty(fileno(stdin)))
  {
    if (argc > 1)
    {
      for (size_t i = 1; i < argc; i++)
      {
        if (i == 1)
        {
          size_t len_arg = strlen(argv[i]) + len_space + 1;
          str = malloc(len_arg * sizeof(*str));
          check_alloc(str);
          strcpy(str, argv[i]);
        }
        else
        {
          size_t len_args = strlen(str) + strlen(argv[i]) + len_space + 1;
          str = realloc(str, len_args * sizeof(*str));
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
        size_t len_str = strlen(buffer) + 1;
        str = malloc(len_str * sizeof(*str));
        check_alloc(str);
        strcpy(str, buffer);
      }
      else
      {
        size_t len_str = strlen(str) + strlen(buffer) + 1;
        str = realloc(str, len_str * sizeof(*str));
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

// ===============================
// ------- 𝙒𝙞𝙙𝙚 𝘾𝙝𝙖𝙧𝙖𝙘𝙩𝙚𝙧 -------
// ===============================
// Consolidate Input From All Sources
void get_winput(int argc, char **argv, wchar_t *res)
{
  wchar_t *str;
  size_t len_space = 1;

  if (isatty(fileno(stdin)))
  {
    if (argc > 1)
    {
      wchar_t **argw = malloc(argc * sizeof(*argw));

      for (size_t i = 0; i < argc; i++)
      {
        size_t len_argv = strlen(argv[i]) + 1;
        argw[i] = malloc(len_argv * sizeof(*argw[i]));
        mbstowcs(argw[i], argv[i], len_argv);
      }
      for (size_t i = 1; i < argc; i++)
      {
        if (i == 1)
        {
          size_t len_arg = wcslen(argw[i]) + len_space + 1;
          str = malloc(len_arg * sizeof(*str));
          check_alloc(str);
          wcscpy(str, argw[i]);
        }
        else
        {
          size_t len_args = wcslen(str) + wcslen(argw[i]) + len_space + 1;
          str = realloc(str, len_args * sizeof(*str));
          check_alloc(str);
          wcscat(str, argw[i]);
        }
        wcscat(str, L" ");
      }
      for(size_t i = 0; i < argc; i++)
      {
        free(argw[i]);
      }
      free(argw);
    }
    else
    {
      str = wcsdup(L"");
      check_alloc(str);
    }
  }
  else
  {
    wchar_t buffer[BUFSIZ];
    int buffer_size = BUFSIZ - 1;
    size_t c = 0;

    while(fgetws(buffer, buffer_size, stdin))
    {
      if (c == 0)
      {
        size_t len_str = wcslen(buffer) + 1;
        str = malloc(len_str * sizeof(*str));
        check_alloc(str);
        wcscpy(str, buffer);
      }
      else
      {
        size_t len_str = wcslen(str) + wcslen(buffer) + 1;
        str = realloc(str, len_str * sizeof(*str));
        check_alloc(str);
        wcscat(str, buffer);
      }
      c++;
    }
  }
  size_t len_str = wcslen(str);

  while(len_str > 0 && str[len_str - 1] == '\n')
  {
    str[--len_str] = '\0';
  }

  wmemcpy(res, str, wcslen(str) + 1);
  free(str);
}
