#include <stdio.h>
#include "printframe.h"

// Frame Builder
void print_frame(Section section, size_t width)
{
  char *char_beg, *char_mid, *char_end;

  switch (section)
  {
    case S_TOP:    char_beg = "╔", char_mid = "═", char_end = "╗"; break;
    case S_SPACER: char_beg = "║", char_mid = " ", char_end = "║"; break;
    case S_BOTTOM: char_beg = "╚", char_mid = "═", char_end = "╝"; break;

    default: return;
  }

  printf("   %s", char_beg);

  for (size_t i = 0; i < width; i++)
  {
    printf("%s", char_mid);
  }

  printf("%s\n", char_end);
}
