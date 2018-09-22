#ifndef PRINTC_H
#define PRINTC_H

#include <stddef.h>

void sprintc(const char *str, size_t len_ctr, char *res);
void swprintc(const wchar_t *str, size_t len_ctr, wchar_t *res);

  /* String Print Centre
   * -------------------
   * Centres string [str] in a space [len_ctr] characters wide and writes it to the address
   * pointed to by [res]. It must have at least [len_ctr] + 1 bytes allocated.
   *
   * Example usage:
   *
   *   char *res = malloc((len_ctr + 1) * sizeof(*res));
   *   sprintc("centre me", len_ctr, res);
   *   [...]
   *   free(res);
   *
   * ------------------- */

void printc(const char *str, size_t len);
void wprintc(const wchar_t *str, size_t len);

  /* Print Centre
   * ------------
   * Wrapper function for sprintf.
   * Prints output directly to stdout.
   * ------------ */

#endif
