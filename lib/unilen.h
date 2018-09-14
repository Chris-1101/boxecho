#ifndef UNILEN_H
#define UNILEN_H

#include <stddef.h>

size_t unilen(const char* str);

  /* Unicode String Length
   * ---------------------
   * C's strlen() function is described as calculating the length of strings. But what it really
   * does is count the amount of bytes in memory allocated to an array, which is not always the
   * same thing. Some characters' codepoints are too large to fit in a single byte and span several
   * bytes. This will throw off strlen's count.
   *
   * unilen() solves this by isolating the top 2 bits of each byte, via a bitwise AND operation
   * against the binary value 11 00 00 00 (0xC0),
   *
   *         xx xx xx xx
   *   AND   11 00 00 00
   *         -- -- -- --
   *     =   xx 00 00 00
   *
   * and then compares them to the binary value 10 00 00 00 (0x80), which will identify subsequent
   * bytes of a multi-byte character set. These can then be omitted from the final count.
   * --------------------- */

  /* UTF-8 and Character Encoding
   * ----------------------------
   * Characters are represented by an 8-bit block, which can hold 2⁸, or 256, different values.
   * In UTF-8 encoding, each character has an associated codepoint or unicode value representing
   * its position in the unicode table. A capital 'A', for instance, is at position 41 and can
   * therefore be stored in a single byte (8-bit block) as the value 00 10 10 01.
   *
   * However, the unicode table holds well over a hundred thousand entries, so a single byte isn't
   * enough to accommodate their representations. To overcome this, UTF-8 has character sets: bytes
   * grouped together to represent a single codepoint. The deeper a character's position in the
   * unicode table, the more bytes are needed to represent it.
   *
   * Being grouped also means these bytes have to store extra information regarding their position
   * in a group and how many subsequent bytes are part of the set. In order to do this, the top-
   * most bits of each byte are reserved.
   *
   * Codepoint   1st Byte   2nd Byte   3rd Byte   4th Byte
   *  ≤    127   0-------
   *  ≤  2,047   110-----   10------
   *  ≤ 65,535   1110----   10------   10------
   *  > 65,535   11110---   10------   10------   10------
   *
   * The remaining free bits are used to store the codepoint.
   * ---------------------------- */

#endif
