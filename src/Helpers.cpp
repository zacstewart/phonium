#include <string.h>

/**
 * Copies `num` bytes from `source` to `destination` and terminates
 * `destination` with a null byte at `num`. `destination` must have
 * room for `num` bytes.
 **/
void *substr(char *destination, const char *source, int num) {
    size_t len = strlen(source);
    if (len < num) {
        num = len;
    }
    memcpy(destination, source, num);
    destination[num] = '\0';
    return destination;
}
