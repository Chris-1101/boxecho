#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "printc.h"
#include "termwidth.h"
#include "checkalloc.h"
#include "getinput.h"
#include "strtrm.h"

// TODO make code wchar-compatible

// Frame Sections
typedef enum Section {
  S_TOP, S_SPACER, S_BOTTOM
} Section;

// Frame Builder
void print_frame(Section section, const size_t width)
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
  size_t width_mid = width -2;

  for (size_t i = 0; i < width_mid; i++)
  {
    strcat(str_frame, char_mid);
  }
  strcat(str_frame, char_end);

  printf("   %s\n", str_frame);
  free(str_frame);
}

// Centre Output
void centre_output(char *str, const size_t len)
{
  char *res = malloc((len + 1) * sizeof(*res));
  check_alloc(res);

  str = strtrm(str, ' ');

  sprintc(str, len, res);
  printf("   ║   %s   ║\n", res);

  free(res);
}

// Wrap Input Based on Terminal Width
void format_output(char *str_input, const size_t len_max)
{
  while(str_input)
  {
    // Pointer to next line feed in string
    char *next_linefeed = strchr(str_input, '\n');

    // Terminate string at next line feed
    next_linefeed && (*next_linefeed = '\0');

    // Length of current line
    size_t len_line = strlen(str_input);

    // ---

    size_t len_total = 0;

    // Print lines that don't exceed max length
    if (len_line <= len_max)
    {
      centre_output(str_input, len_max);
    }
    else // Build line word by word
    {
      char *words, *cache;
      char *str_builder = malloc((len_max + 1) * sizeof(*str_builder));
      check_alloc(str_builder);
      memset(str_builder, 0, len_max);

      // Break line into a sequence of words
      words = strtok_r(str_input, " ", &cache);

      while(words != NULL)
      {
        size_t len_word = strlen(words);
        len_total += len_word;

        // Replace long words to avoid infinite loops
        if (len_word > len_max)
        {
          strcpy(words, "[...]");
          len_total += 5 - len_word;
        }

        // Add word to line as long as its length doesn't exceed len_max
        if (len_total <= len_max)
        {
          strcat(str_builder, words);
        }
        else // Reset and add word to 'new' line
        {
          centre_output(str_builder, len_max);
          strcpy(str_builder, words);
          len_total = len_word;
        }

        // Add space after every word, unless EOL
        if (len_total + 1 < len_max)
        {
          strcat(str_builder, " ");
          len_total++;
        }

        // Required by strtok_r()
        words = strtok_r(NULL, " ", &cache);
      }

      // Print last line, free alloc'd memory
      centre_output(str_builder, len_max);
      free(str_builder);
    }

    // ---

    // Restore line feed at original position
    next_linefeed && (*next_linefeed = '\n');

    // Move pointer to next LF in memory or terminate loop
    str_input = next_linefeed ? (next_linefeed + 1) : NULL;
  }
}

// --- Box Echo Entry Point ---
int main(int argc, char **argv)
{
  // Normalise Input
  char *str_input = malloc(BUFSIZ * sizeof(*str_input));
  check_alloc(str_input);
  get_input(argc, argv, str_input);

  // Simulate echo's behaviour with no input
  if ((str_input != NULL) && (str_input[0] == '\0'))
  {
    printf("\n");
    return 0;
  }

  // Terminal, frame & max content width
  Width *width = malloc(sizeof(*width));
  check_alloc(width);
  get_term_width(width);

  // Guard against overly-narrow windows
  const size_t MIN_WIDTH = 30;

  if (width->TERM <= MIN_WIDTH)
  {
    fprintf(stderr, "Terminal too narrow");
    return 1;
  }

  // ---

  printf("\n");
  print_frame(S_TOP, width->FRAME);
  print_frame(S_SPACER, width->FRAME);
  format_output(str_input, width->CONTENT);
  print_frame(S_SPACER, width->FRAME);
  print_frame(S_BOTTOM, width->FRAME);
  printf("\n");

  // ---

  free(str_input);
  free(width);

  return 0;
}
