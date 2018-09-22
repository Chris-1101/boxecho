#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include "strtrm.h"

// =================================
// ------- 𝙉𝙖𝙧𝙧𝙤𝙬 𝘾𝙝𝙖𝙧𝙖𝙘𝙩𝙚𝙧 -------
// =================================
// Trim Character From String Start/End
char *strtrm(char *str, const char chr)
{
  if (str == NULL)
  {
    return NULL;
  }

  size_t len_str = strlen(str);

  while(len_str > 0 && str[0] == chr)
  {
    str++;
    len_str--;
  }

  while(len_str > 0 && str[len_str - 1] == chr)
  {
    str[--len_str] = L'\0';
  }

  return str;
}

// ===============================
// ------- 𝙒𝙞𝙙𝙚 𝘾𝙝𝙖𝙧𝙖𝙘𝙩𝙚𝙧 -------
// ===============================
// Trim Character From String Start/End
wchar_t *wcstrm(wchar_t *str, const wchar_t chr)
{
  if (str == NULL)
  {
    return NULL;
  }

  size_t len_str = wcslen(str);

  while(len_str > 0 && str[0] == chr)
  {
    str++;
    len_str--;
  }

  while(len_str > 0 && str[len_str - 1] == chr)
  {
    str[--len_str] = L'\0';
  }

  return str;
}
