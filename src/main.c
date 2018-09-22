#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>

#include "printc.h"
#include "termwidth.h"
#include "checkalloc.h"
#include "getinput.h"
#include "strtrm.h"

// ====================================
// ------- 𝙁𝙪𝙣𝙘𝙩𝙞𝙤𝙣　𝘿𝙚𝙛𝙞𝙣𝙞𝙩𝙞𝙤𝙣𝙨 -------
// ====================================
// Frame Sections
typedef enum Section {
  S_TOP, S_SPACER, S_BOTTOM
} Section;

// Frame Builder
void print_frame(Section section, const size_t width)
{
  wchar_t *char_beg, *char_mid, *char_end;

  wchar_t *str_frame = malloc((width + 1) * sizeof(*str_frame));
  check_alloc(str_frame);

  switch (section)
  {
    case S_TOP:    char_beg = L"╔", char_mid = L"═", char_end = L"╗"; break;
    case S_SPACER: char_beg = L"║", char_mid = L" ", char_end = L"║"; break;
    case S_BOTTOM: char_beg = L"╚", char_mid = L"═", char_end = L"╝"; break;

    default: return;
  }

  wcscpy(str_frame, char_beg);
  size_t width_mid = width - 2;

  for (size_t i = 0; i < width_mid; i++)
  {
    wcscat(str_frame, char_mid);
  }
  wcscat(str_frame, char_end);

  wprintf(L"   %ls\n", str_frame);
  free(str_frame);
}

// Centre Output
void centre_output(wchar_t *str, const size_t len)
{
  wchar_t *res = malloc((len + 1) * sizeof(*res));
  check_alloc(res);

  str = wcstrm(str, L' ');

  swprintc(str, len, res);
  wprintf(L"   ║   %ls   ║\n", res);

  free(res);
}

// Wrap Input Based on Terminal Width
void format_output(wchar_t *str_input, const size_t len_max)
{
  while(str_input)
  {
    // Pointer to next line feed in string
    wchar_t *next_linefeed = wcschr(str_input, L'\n');

    // Terminate string at next line feed
    next_linefeed && (*next_linefeed = L'\0');

    // Length of current line
    size_t len_line = wcslen(str_input);

    // ---

    size_t len_total = 0;

    // Print lines that don't exceed max length
    if (len_line <= len_max)
    {
      centre_output(str_input, len_max);
    }
    else // Build line word by word
    {
      wchar_t *words, *cache;
      wchar_t *str_builder = calloc(len_max + 1, sizeof(*str_builder));
      check_alloc(str_builder);

      // Break line into a sequence of words
      words = wcstok(str_input, L" ", &cache);

      while(words != NULL)
      {
        size_t len_word = wcslen(words);
        len_total += len_word;

        // Replace long words to avoid infinite loops
        if (len_word > len_max)
        {
          wcscpy(words, L"[...]");
          len_total += 5 - len_word;
        }

        // Add word to line as long as its length doesn't exceed len_max
        if (len_total <= len_max)
        {
          wcscat(str_builder, words);
        }
        else // Reset and add word to 'new' line
        {
          centre_output(str_builder, len_max);
          wcscpy(str_builder, words);
          len_total = len_word;
        }

        // Add space after every word, unless EOL
        if (len_total + 1 < len_max)
        {
          wcscat(str_builder, L" ");
          len_total++;
        }

        // Required by strtok_r()
        words = wcstok(NULL, L" ", &cache);
      }

      // Print last line, free alloc'd memory
      centre_output(str_builder, len_max);
      free(str_builder);
    }

    // ---

    // Restore line feed at original position
    next_linefeed && (*next_linefeed = L'\n');

    // Move pointer to next LF in memory or terminate loop
    str_input = next_linefeed ? (next_linefeed + 1) : NULL;
  }
}

// ===========================
// ------- 𝙀𝙣𝙩𝙧𝙮 𝙋𝙤𝙞𝙣𝙩 -------
// ===========================
int main(int argc, char **argv)
{
  // Retrieve locale from environment for wide char encoding
  setlocale(LC_CTYPE, "");

  // Normalise different forms of input
  wchar_t *str_input = calloc(BUFSIZ, sizeof(*str_input));
  check_alloc(str_input);
  get_winput(argc, argv, str_input);

  // Simulate echo's behaviour with no input
  if ((str_input != NULL) && str_input[0] == L'\0')
  {
    wprintf(L"\n");
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
    // No need to use wchar-aware function here
    // Character orientation of stderr stream is still byte
    fprintf(stderr, "Terminal too narrow");
    return 1;
  }

  // ---

  wprintf(L"\n");
  print_frame(S_TOP, width->FRAME);
  print_frame(S_SPACER, width->FRAME);
  format_output(str_input, width->CONTENT);
  print_frame(S_SPACER, width->FRAME);
  print_frame(S_BOTTOM, width->FRAME);
  wprintf(L"\n");

  // ---

  free(str_input);
  free(width);

  return 0;
}
