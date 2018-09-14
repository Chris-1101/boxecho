#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "printc.h"

// String-Print Centre
void sprintc(const char *str, size_t len_ctr, char *res)
{
  size_t len_str = strlen(str);

  if (len_str >= len_ctr) {
    strcpy(res, str);
    return;
  }

  short parity_str = len_str % 2;
  short parity_ctr = len_ctr % 2;

  char parity_shift[] = "";

  if (parity_ctr != parity_str)
  {
    parity_shift[0] = ' ';
    len_str++;
  }

  size_t len_padding = (len_ctr - len_str) / 2;
  char *padding = calloc(len_padding + 1, sizeof(*padding));

  if (!padding)
  {
    fprintf(stderr, "Error allocating memory in sprintc()");
    abort();
  }

  memset(padding, ' ', len_padding);

  sprintf(res, "%s%s%s%s", padding, parity_shift, str, padding);
  free(padding);
}

// Print Centre
void printc(const char *str, size_t len)
{
  char *output = malloc(len * sizeof(*output));

  if (!output)
  {
    fprintf(stderr, "Error allocating memory in printc()");
    abort();
  }

  sprintc(str, len, output);
  printf("%s\n", output);

  free(output);
}
