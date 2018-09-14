#include <stddef.h>
#include "unilen.h"

// Count UTF-8 Characters
size_t unilen(const char* str)
{
  // No magic numbers here!
  const int TOP_2_BITS = 0xC0;         // 11 00 00 00
  const int CONTINUATION_BYTE = 0x80;  // 10 00 00 00

  // Initialise index and count variables
  size_t byte_index = 0;
  size_t char_count = 0;

  // Count characters by counting the amount of bytes,
  // excluding those whose top 2 bits evaluate to being
  // part of a character's multi-byte sequence
  while(str[byte_index])
  {
    if ((str[byte_index] & TOP_2_BITS) != CONTINUATION_BYTE)
      char_count++;
    byte_index++;
  }

  // Return count
  return char_count;
}
