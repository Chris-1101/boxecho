#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "printc.h"
#include "checkalloc.h"

// =================================
// ------- 𝙉𝙖𝙧𝙧𝙤𝙬 𝘾𝙝𝙖𝙧𝙖𝙘𝙩𝙚𝙧 -------
// =================================
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

  char parity_shift[2] = "";

  if (parity_ctr != parity_str)
  {
    strcpy(parity_shift, " ");
    len_str++;
  }

  size_t len_padding = (len_ctr - len_str) / 2;
  char *padding = calloc(len_padding + 1, sizeof(*padding));
  check_alloc(padding);
  memset(padding, ' ', len_padding);

  sprintf(res, "%s%s%s%s", padding, parity_shift, str, padding);
  free(padding);
}

// Print Centre
void printc(const char *str, size_t len)
{
  char *output = malloc(len * sizeof(*output));
  check_alloc(output);

  sprintc(str, len, output);
  printf("%s\n", output);

  free(output);
}

// ===============================
// ------- 𝙒𝙞𝙙𝙚 𝘾𝙝𝙖𝙧𝙖𝙘𝙩𝙚𝙧 -------
// ===============================
// String-Print Centre
void swprintc(const wchar_t *str, size_t len_ctr, wchar_t *res)
{
  size_t len_str = wcslen(str);

  if (len_str >= len_ctr) {
    wcscpy(res, str);
    return;
  }

  short parity_str = len_str % 2;
  short parity_ctr = len_ctr % 2;

  wchar_t parity_shift[2] = L"";

  if (parity_ctr != parity_str)
  {
    wcscpy(parity_shift, L" ");
    len_str++;
  }

  size_t len_padding = (len_ctr - len_str) / 2;
  wchar_t *padding = calloc(len_padding + 1, sizeof(*padding));
  check_alloc(padding);
  wmemset(padding, L' ', len_padding);

  size_t len_res = (wcslen(padding) * 2) + wcslen(parity_shift) + wcslen(str) + 1;

  swprintf(res, len_res, L"%ls%ls%ls%ls", padding, parity_shift, str, padding);
  free(padding);
}

// Print Centre
void wprintc(const wchar_t *str, size_t len)
{
  wchar_t *output = malloc(len * sizeof(*output));
  check_alloc(output);

  swprintc(str, len, output);
  wprintf(L"%s\n", output);

  free(output);
}
