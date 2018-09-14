#ifndef TERMWIDTH_H
#define TERMWIDTH_H

#include <stddef.h>

typedef struct Width {
  const unsigned short TERM;
  const unsigned short FRAME;
  const unsigned short CONTENT;
} Width;

  /* Width structure
   * ---------------
   * Struct holding several relevant dimensions.
   *
   *  · TERM: terminal width, equivalent to tput cols
   *  · FRAME: padded from the side of the terminal
   *  · CONTENT: padded from the side of the frame
   *
   * ---------------
   */

void get_term_width(Width *w);

  /* Get Terminal Width
  * ------------------
  * Uses ioctl() to fill a winsize struct from which the relevant
  * information needed to fill our own Width struct is extracted.
  *
  * Expects a pointer with adequately allocated memory within
  * which to write the new Width struct.
  * ------------------
  */

#endif
