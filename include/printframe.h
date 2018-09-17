#ifndef PRINTFRAME_H
#define PRINTFRAME_H

#include <stddef.h>

typedef enum Section {
  S_TOP, S_SPACER, S_BOTTOM
} Section;

  /* Section Enumeration
   * -------------------
   * Stores named constants corresponding
   * to each frame section.
   * -------------------
   */

void print_frame(Section section, size_t width);

  /* Print Frame Section
   * -------------------
   * Prints individual sections of a frame that stretches the specified width.
   * Valid sections are members of the Section enumeration.
   *
   * · S_TOP    :    ╔══════════════════════════════════════╗
   * · S_SPACER :    ║                                      ║
   * · S_BOTTOM :    ╚══════════════════════════════════════╝
   *
   *    [width]   ├────────────────────────────────────────────┤
   *
   * -------------------
   */

#endif
