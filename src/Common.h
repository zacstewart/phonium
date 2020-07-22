#ifndef COMMON
#define COMMON

#include <stddef.h>

#define COLOR_BLACK 0
#define COLOR_WHITE 1
#define DISPLAY_HEIGHT 200
#define DISPLAY_WIDTH 200
#define MESSAGE_LENGTH 160
#define NUMBER_LENGTH 30

/**
 * Formats a time duration in milliseconds to HH:MM[:SS]
 * @param unsigned long time in miliseconds
 * @param bool include seconds [optional, default true]
 */
char * formatTime(unsigned long, bool = true);

/**
 * Copies `num` bytes from `source` to `destination` and terminates
 * `destination` with a null byte at `num`. `destination` must have
 * room for `num` bytes.
 **/
void *substr(char *, const char *, int);

#endif
