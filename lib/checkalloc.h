#ifndef CHECKALLOC_H
#define CHECKALLOC_H

void check_alloc_spec(const void *ptr, const char *caller);

  /* Check Memory Allocation
   * -----------------------
   * Performs a null pointer check on ptr.
   * Prints error and aborts execution if pointer is null.
   * Intended to be used after malloc() & family.
   * -----------------------
   */

#define check_alloc(ptr) check_alloc_spec(ptr, __func__)

  /* Wrapper Macro
   * -------------
   * Passes the name of the calling function.
   * -------------
   */

#endif
