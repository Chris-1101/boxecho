#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "printc.h"
#include "termwidth.h"
#include "printframe.h"
#include "checkalloc.h"

// TODO makefile

// Centre Output
void centre_output(char *str, const size_t len)
{
  char *res = malloc((len + 1) * sizeof(*res));
  check_alloc(res);

  // TODO trim leading/trailing spaces
  sprintc(str, len, res);
  printf("   ║   %s   ║\n", res);

  free(res);
}

// Wrap Input Based on Terminal Width
void format_output(char *str_input, size_t len_max)
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
      char *str_builder = malloc(len_max * sizeof(*str_builder) + 1);
      check_alloc(str_builder);

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

// TODO normalise_input()

// --- Box Echo Entry Point ---
int main(int argc, char **argv)
{
  // TODO Replace with normalise_input() call
  char str_input[] = "\"Throughout a ship's lifespan, the parts of it that weather and decay are gradually replaced and the old parts are stored. Once every part of the ship has been entirely replaced, withareallylongwordthatsgoingtoteartheterminaltopieccesandreallybadeggsyohohothrowinsomebottlesofrumtoo piece by piece, can it still be considered the same ship? Furthermore, if you were to take all of the old pieces that you stored and used to build another ship, would this be the original ship?\"\n\n-- The Ship of Theseus";

  char *ptr_input = &str_input[0];

  // Simulate echo's behaviour with no input
  if ((ptr_input != NULL) && (ptr_input[0] == '\0'))
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
  format_output(ptr_input, width->CONTENT);
  print_frame(S_SPACER, width->FRAME);
  print_frame(S_BOTTOM, width->FRAME);
  printf("\n");

  // ---

  free(width);

  return 0;
}
