#include <stdlib.h>
#include <stdint.h>

// Input to this function is an array of exactly 12 bytes.
// The bytes represent a big-endian 96-bit number.
// This function should increment the number by 1 in-place.
// There is no return value.

void ctr96_inc(unsigned char *counter) { //***
    uint32_t n = 12, c = 1;

    do {
        --n;
        c += counter[n];
        counter[n] = (uint8_t)c;
        c >>= 8;
    } while (n);
}
// HUMAN NOTE: from OpenSSL providers/implementations/rands/drbg_ctr.c - changes made

//***
unsigned char value0[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
unsigned char answer0[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2};
ctr96_inc(value0);
assert(memcmp(value0, answer0, 12) == 0);


unsigned char value1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0x03, 0xFF, 0xFF};
unsigned char answer1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0x04, 0x00, 0x00};
ctr96_inc(value1);
assert(memcmp(value1, answer1, 12) == 0);


unsigned char value2[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
unsigned char answer2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
ctr96_inc(value2);
assert(memcmp(value2, answer2, 12) == 0);
