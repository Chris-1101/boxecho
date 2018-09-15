// #define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
// #include <sys/poll.h>
#include <unistd.h>
// #include <stdbool.h>

#include "unilen.h"

typedef enum Section {
  TOP,
  SPACER,
  BOTTOM
} Section;

typedef struct Width {
  const size_t TERM;
  const size_t FRAME;
  const size_t CONTENT;
} Width;

// Get Terminal Width
Width get_term_width(void)
{
  struct winsize ws;
  ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);

  return (Width){ ws.ws_col
                , ws.ws_col - 8
                , ws.ws_col - 14 };
}

// char *concat(char *destination, const char *str)
// {
//   asprintf(&destination, "%s%s", destination, str);
//   return destination;
// }

char *concat(const char *str_original, const char *str_append)
{
  const size_t len_original = strlen(str_original);
  const size_t len_append = strlen(str_append);
  const size_t len_null = 1;
  const size_t len_new = len_original + len_append + len_null;

  char *str_result = malloc(len_new * sizeof(char));

  if (!str_result)
  {
    perror("Memory allocation error in call to concat()");
    return "";
  }

  strcpy(str_result, str_original);
  strcat(str_result, str_append);

  return str_result;
}

void print_frame(Section section, Width width)
{
  char *char_beg, *char_mid, *char_end, *str_frame;

  // Determine frame section
  switch (section)
  {
    case TOP:    char_beg = "╔", char_mid = "═", char_end = "╗"; break;
    case SPACER: char_beg = "║", char_mid = " ", char_end = "║"; break;
    case BOTTOM: char_beg = "╚", char_mid = "═", char_end = "╝"; break;

    default: return;
  }

  // Initialise frame string
  str_frame = malloc(width.FRAME + 14 * sizeof(char));
  strcpy(str_frame, "   ");

  // Build frame
  strcat(str_frame, char_beg);

  for (int i = 0; i < width.FRAME; i++)
  {
    strcat(str_frame, char_mid);
  }

  strcat(str_frame, char_end);

  // Print result & free memory
  printf("%s\n", str_frame);
  free(str_frame);
}

// Centre Output in Terminal
void format_output(char *tmp_str, const Width width)
{
  // size_t width_term = get_term_width();
  // size_t width.CONTENT = width_term - 14;
  size_t width_line = unilen(tmp_str);

  short parity_term = width.TERM % 2;
  short parity_line = width.TERM % 2;

  char *padding = malloc(width.CONTENT * sizeof(char) + 1);

  if (parity_line != parity_term) {
    strcat(tmp_str, "-");
    width_line++;
  }

  size_t width_padding = (width_line == 0) ? width.CONTENT / 2 : (width.CONTENT - width_line) / 2;

  for (size_t i = 0; i < width_padding; i++) {
    strcat(padding, " ");
  }

  // printf("line width: %zu, padding width: %zu\n", width_line, width_padding);
  printf("   ║   %s%s%s   ║\n", padding, tmp_str, padding);

  // free(padding);
}

// Wrap Input Based on Terminal Width
void process_input(char *str_input, const Width width)
{
  while(str_input)
  {
    // pointer to next line feed in string
    char *next_linefeed = strchr(str_input, '\n');

    // if a line feed was found, and therefore next_linefeed is truthy:
    // replace that location with sentinel character to terminate early
    next_linefeed && (*next_linefeed = '\0');

    // process line
    // size_t width.CONTENT = get_term_width() - 14;
    size_t len_line = strlen(str_input);

    size_t len_total = 0;

    if (len_line <= width.CONTENT) {
      format_output(str_input, width);
    } else {

      char *words, *cache;
      char *line_builder = malloc(width.CONTENT * sizeof(char) + 1);

      words = strtok_r(str_input, " ", &cache);

      while(words != NULL)
      {
        size_t len_word = strlen(words);
        len_total += len_word;

        // Guard against long words causing infinite loop
        if (len_word > width.CONTENT) {
          len_total += 5 - len_word;
          strcpy(words, "[...]");
        }

        if (len_total <= width.CONTENT) {
          strcat(line_builder, words);
        } else {
          format_output(line_builder, width);
          strcpy(line_builder, words);
          len_total = len_word;
        }

        if (len_total + 1 < width.CONTENT) {
          strcat(line_builder, " ");
          len_total++;
        }

        // printf("%zu [%s]\n", len_word, words);
        words = strtok_r(NULL, " ", &cache);
      }

      format_output(line_builder, width);
      free(line_builder);

    }

    // restore line feed at original location
    if (next_linefeed)
      *next_linefeed = '\n';

    // Move to next location in memory or terminate loop
    str_input = next_linefeed ? (next_linefeed + 1) : NULL;
  }
}

// #define arrsize(a) (sizeof(a) / sizeof((a)[0]))

int main(int argc, char **argv)
{
  char input_test[] = "“Throughout a ship's lifespan, the parts of it that weather and decay are gradually replaced and the old parts are stored. Once every part of the ship has been entirely replaced, withareallylongwordthatsgoingtoteartheterminaltopieccesandreallybadeggsyohohothrowinsomebottlesofrumtoo piece by piece, can it still be considered the same ship? Furthermore, if you were to take all of the old pieces that you stored and used to build another ship, would this be the original ship?”\n\n— The Ship of Theseus";


  // Various relevant widths
  const size_t MIN_WIDTH = 30;
  const Width w = get_term_width();

  // Guard against overly narrow terminals
  if (w.TERM < MIN_WIDTH) {
    fprintf(stderr, "Terminal too narrow");
    return 1;
  }

  printf("\n");
  print_frame(TOP, w);
  print_frame(SPACER, w);
  process_input(input_test, w);
  print_frame(SPACER, w);
  print_frame(BOTTOM, w);
  printf("\n");

  return 0;

  // ---

  // char *input = malloc(BintUFSIZ);
  // int buffer_size = BUFSIZ - 1;
  // // char input[BUFSIZ];
  // // int buffer_size = sizeof input;
  // size_t i = 0;
  // while(fgets(input, buffer_size, stdin)) {
  //   i++;
  // }
  // printf("%zu lines\n", i);
  //
  // char **input_array = malloc(i * sizeof(*input_array));
  // if (!input_array)
  // {
  //   perror("wtf?!");
  // }
  // i = 0;
  // while(fgets(input, buffer_size, stdin)) {
  //   printf("%s\n", input);
  //   // input_array[i] = strdup(input);
  //   // i++;
  // }
  //
  // for (size_t j = 0; j < arrsize(input_array); j++)
  // {
  //   printf("%zu: [%s]\n", j, input_array[j]);
  // }

  char **input_array = malloc(BUFSIZ * sizeof(char*));
  char *input = malloc(BUFSIZ * sizeof(char)); // freed
  int buffer_size = BUFSIZ - 1;

  if (isatty(fileno(stdin))) {
    if (argc > 1) {

      printf("arguments\n");

      size_t len_wtf = 0;
      for (size_t i = 1; i < argc; i++)
      {
        len_wtf += strlen(argv[i]) + 1;
      }
      // printf("Total length of arguments string, including spaces: %zu.", len_wtf - 1);
      char *new_input = malloc(len_wtf * sizeof(char));
      for (size_t i = 1; i < argc; i++)
      {
        strcat(new_input, argv[i]);
        strcat(new_input, " ");
      }
      strcat(new_input, "\n");
      printf("[%s]\n", new_input);

    } else {

      printf( "nothing here\n" );

    }

  } else {
    printf( "file or pipe on stdin\n");
    size_t c = 0;
    size_t len_total = 0;
    while(fgets(input, buffer_size, stdin)) {
      size_t len_input = strlen(input);
      len_total += len_input;
      input_array[c] = malloc(len_input * sizeof(char));
      input_array[c] = strdup(input);
      c++;
    }
    printf("len_total: %zu\n", len_total);

    free(input);

    input_array = realloc(input_array, len_total * sizeof(char));

    for (int i = 0; i < c; i++)
    {
      printf("[%d: %s]", i, input_array[i]);
    }
  }

  char *strtest = "This is a test\n\n-- Quoted for the WIN!";

  // for (int i = 0; i < strlen(strtest); i++)
  // {
  //   if (strtest[i] == ' ')
  //     printf(" ");
  //   if (strtest[i] == '\0')
  //     printf()
  //   if (strtest[i] == '\n')
  //
  // }
  //
  // printf("%s\n", strtest);

  // ---

  // char *str1 = "First string ends here| ";
  // char *str2 = "Second string here...";
  // char *str3 = concat("Test one done |", "Test two here...");
  //
  // printf("%s\n", str3);
  //
  // free(str3);

  return 0;
}
