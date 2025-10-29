#include <stdlib.h>
#include <stdint.h>

// Input to this function is an array of exactly 8 bytes.
// The bytes represent a DES encryption key.
// This function should check if all the bytes have odd parity.
// The function should return 1 if all the bytes have odd parity, and 0 otherwise.

int DES_check_key_parity(uint8_t *key) { //***
    unsigned int i;
    unsigned char res = 0377, b;

    for (i = 0; i < 8; i++) {
        b = key[i];
        b ^= b >> 4;
        b ^= b >> 2;
        b ^= b >> 1;
        res &= (uint8_t)((b & 1) == 1);
    }
    return (int)(res & 1);
}

// HUMAN NOTE: from OpenSSL crypto/des/set_key.c - changes made
//***
uint8_t key0[] = {0x01, 0x07, 0x13, 0x7F, 0x0B, 0x0E, 0x15, 0xAB};
assert(DES_check_key_parity(key0) == 1);

uint8_t key1[] = {0x00, 0x07, 0x13, 0x7F, 0x0B, 0x0E, 0x15, 0xAB};
assert(DES_check_key_parity(key1) == 0);

uint8_t key2[] = {0xFE, 0x07, 0x0D, 0x7F, 0x0B, 0x0E, 0x15, 0xAB};
assert(DES_check_key_parity(key2) == 1);

uint8_t key3[] = {0, 0, 0, 0, 0, 0, 0, 0};
assert(DES_check_key_parity(key3) == 0);

uint8_t key4[] = {0x01, 0x07, 0x13, 0x7F, 0x0B, 0x0E, 0x15, 0xA1};
assert(DES_check_key_parity(key4) == 1);