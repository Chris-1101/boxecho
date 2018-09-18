#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "printframe.h"
#include "checkalloc.h"

// Frame Builder
void print_frame(Section section, size_t width)
{
  char *char_beg, *char_mid, *char_end;

  char *str_frame = malloc((width + 1) * sizeof(*str_frame));
  check_alloc(str_frame);

  switch (section)
  {
    case S_TOP:    char_beg = "╔", char_mid = "═", char_end = "╗"; break;
    case S_SPACER: char_beg = "║", char_mid = " ", char_end = "║"; break;
    case S_BOTTOM: char_beg = "╚", char_mid = "═", char_end = "╝"; break;

    default: return;
  }

  strcpy(str_frame, char_beg);

  for (size_t i = 0; i < width; i++)
  {
    strcat(str_frame, char_mid);
  }
  strcat(str_frame, char_end);

  printf("   %s\n", str_frame);
  free(str_frame);
}
