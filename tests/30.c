#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Circular shift the digits of the integer x, shift the digits right by shift
// and return the result as a string allocated on the heap
// If shift > number of digits, return digits reversed.
// x should be a 64-bit integer.
/// circular_shift(12, 1) -> "21"
/// circular_shift(12, 2) -> "12"

char* circular_shift(long long x, int shift) { //***
    if (x == 0) {
        return strdup("0");
    }

    int space = ceil(log10(x)) + 2;
    char* number = (char*)malloc(space);
    snprintf(number, space, "%lld", x);

    int length = strlen(number);
    char* result = strdup(number);

    if (shift > length) {
        for (int i = 0; i < length; i++) {
            result[length - i - 1] = number[i];
        }

    } else if (shift > 0) {
        for (int i = 0; i < length; i++) {
            result[(i + shift) % length] = number[i];
        }
    }

    free(number);
    return result;
}
//HUMAN NOTE: modified from humaneval task 65 - changes made
//***
assert(strcmp(circular_shift(###0I###, ###1I###), ###_S###) == 0);
