#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
// #include <unistd.h>

typedef enum Section Section;
enum Section
{
  TOP,
  SPACER,
  BOTTOM
};

typedef struct Width Width;
struct Width
{
  const int TERM;
  const int FRAME;
  const int CONTENT;
};

int get_term_width()
{
  struct winsize ws;
  ioctl(0, TIOCGWINSZ, &ws);

  return ws.ws_col;
}

char *concat(char *destination, const char *str)
{
  asprintf(&destination, "%s%s", destination, str);
  return destination;
}

void build_frame(Section section, int width)
{
  char *char_beg, *char_mid, *char_end;

  switch (section)
  {
    case TOP:
      char_beg = "╔";
      char_mid = "═";
      char_end = "╗";
      break;

    case SPACER:
      char_beg = "║";
      char_mid = " ";
      char_end = "║";
      break;

    case BOTTOM:
      char_beg = "╚";
      char_mid = "═";
      char_end = "╝";
      break;

    default: return;
  }

  char *string_builder = "   ";
  string_builder = concat(string_builder, char_beg);
  // asprintf(&string_builder, "%s%s", string_builder, char_beg);

  for (int i = 0; i < width; i++)
  {
    // asprintf(&string_builder, "%s%s", string_builder, char_mid);
    string_builder = concat(string_builder, char_mid);
  }

  string_builder = concat(string_builder, char_end);
  // asprintf(&string_builder, "%s%s", string_builder, char_end);
  printf("%s\n", string_builder);
  free(string_builder);
}

int main(int argc, char *argv[])
{
  Width width = {
    get_term_width(),
    width.TERM - 8,
    width.FRAME - 6
  };

  Section SECTION_TOP = TOP;
  Section SECTION_SPACER = SPACER;
  Section SECTION_BOTTOM = BOTTOM;

  printf("\n");
  build_frame(SECTION_TOP, width.FRAME);
  build_frame(SECTION_SPACER, width.FRAME);
  build_frame(SECTION_SPACER, width.FRAME);
  build_frame(SECTION_BOTTOM, width.FRAME);
  printf("\n");

  return 0;
}
