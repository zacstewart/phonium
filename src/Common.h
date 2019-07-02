#ifndef COMMON
#define COMMON

#include <stddef.h>

#define COLOR_BLACK 0
#define COLOR_WHITE 1
#define DISPLAY_HEIGHT 144
#define DISPLAY_WIDTH 168
#define MESSAGE_LENGTH 160
#define NUMBER_LENGTH 30

/**
 * Formats a time duration in milliseconds to HH:MM[:SS]
 * @param unsigned long time in miliseconds
 * @param bool include seconds [optional, default true]
 */
char * formatTime(unsigned long, bool = true);

#endif
