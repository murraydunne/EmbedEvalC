#include <stdlib.h>

// Reverse a buffer.
// If in is not NULL, then reverse the contents of in and place the result in out.
// If in is NULL, reverse out in-place.
// size is the number of bytes in the array to be reversed.
// There is no return value.

void BUF_reverse(unsigned char *out, const unsigned char *in, size_t size) { //***
    size_t i;
    if (in) {
        out += size - 1;
        for (i = 0; i < size; i++)
            *out-- = *in++;
    } else {
        unsigned char *q;
        char c;
        q = out + size - 1;
        for (i = 0; i < size / 2; i++) {
            c = *q;
            *q-- = *out;
            *out++ = c;
        }
    }
}
// HUMAN NOTE: from OpenSSL crypto/buffer/buffer.c - changes made
//***

const char* in0 = "hello";
char* out0 = (char*)malloc(5); // yes 5, not 6
BUF_reverse(out0, in0, 5);
assert(memcmp(out0, "olleh", 5) == 0);
free(out0);

const char* in1 = "hello";
char* out1 = (char*)malloc(5); // yes 5, not 6
out1[4] = 't';
out1[5] = 't';
BUF_reverse(out1, in1, 3);
assert(memcmp(out1, "lehtt", 3) == 0);
free(out1);

char* in2 = (char*)malloc(3);
in2[0] = 'a';
in2[1] = 'b';
in2[2] = 'c';
BUF_reverse(in2, NULL, 2);
assert(memcmp(in2, "bac", 3) == 0);
free(in2);