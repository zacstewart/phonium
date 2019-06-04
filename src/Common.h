#ifndef COMMON
#define COMMON

#include <stddef.h>

#define COLOR_WHITE EPD_WHITE
#define COLOR_BLACK EPD_BLACK
#define COLOR_GRAY EPD_RED
#define NUMBER_LENGTH 30
#define MESSAGE_LENGTH 160

/**
 * Formats a time duration in milliseconds to HH:MM[:SS]
 * @param unsigned long time in miliseconds
 * @param bool include seconds [optional, default true]
 */
char * formatTime(unsigned long, bool = true);

#endif
