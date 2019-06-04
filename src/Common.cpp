#include "Arduino.h"

char * formatTime(unsigned long t, bool includeSec = true) {
  static char str[9];

  t = t / 1000; // Drop milliseconds
  int h = t / 3600;
  t = t % 3600;
  int m = t / 60;
  int s = t % 60;

  sprintf(str, "%02d:%02d:%02d", h, m, s);
  return str;
}
