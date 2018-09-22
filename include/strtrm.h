#ifndef TRIMCHAR_H
#define TRIMCHAR_H

char *strtrm(char *str, const char chr);
wchar_t *wcstrm(wchar_t *str, const wchar_t chr);

  /* Trim Character From String
   * --------------------------
   * Trims the character specified in [chr]
   * from the beginning and end of [str].
   *
   * Returns a pointer to a null-terminated substring of the
   * original. Must be able to write to the original string.
   * --------------------------
   */

#endif
