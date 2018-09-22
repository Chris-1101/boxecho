#ifndef INPUT_H
#define INPUT_H

void get_input(int argc, char **argv, char *str);
void get_winput(int argc, char **argv, wchar_t *res);

  /* Get Input From All Sources
   * --------------------------
   * Consolidates input from command line arguments,
   * pipe, redirection and here string into [str]
   *
   * The pointer passed to [str] must
   * have enough memory allocated.
   * --------------------------
   */

#endif
