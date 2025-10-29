#include <stddef.h>
#include <stdint.h>

#define OSSL_BSEARCH_VALUE_ON_NOMATCH            0x01
#define OSSL_BSEARCH_FIRST_VALUE_ON_MATCH        0x02

// Binary searches the sorted array base for the value key.
// base contains num items of size size.
// The search is done using the compare function cmp
// which takes two pointers to the items to be compared.
// Flags is a bitwise flag with two options:
//   - if OSSL_BSEARCH_VALUE_ON_NOMATCH is set, return the
//       closest item to the key if the key is not found
//       otherwise return NULL if the key is not found
//   - if OSSL_BSEARCH_FIRST_VALUE_ON_MATCH is set, return
//       first item matching the key if there are multiple
//       contiguous matches
const void *ossl_bsearch(const void *key, const void *base, int num,
                         int size, int (*cmp) (const void *, const void *),
                         int flags) { //***
    const char *base_ = base;
    int l, h, i = 0, c = 0;
    const char *p = NULL;

    if (num == 0)
        return NULL;
    l = 0;
    h = num;
    while (l < h) {
        i = (l + h) / 2;
        p = &(base_[i * size]);
        c = (*cmp) (key, p);
        if (c < 0)
            h = i;
        else if (c > 0)
            l = i + 1;
        else
            break;
    }
    if (c != 0 && !(flags & OSSL_BSEARCH_VALUE_ON_NOMATCH))
        p = NULL;
    else if (c == 0 && (flags & OSSL_BSEARCH_FIRST_VALUE_ON_MATCH)) {
        while (i > 0 && (*cmp) (key, &(base_[(i - 1) * size])) == 0)
            i--;
        p = &(base_[i * size]);
    }
    return p;
}
// HUMAN NOTE: from OpenSSL crypto/bsearch.c - changes made
//***
int cmp0(const void* a, const void* b) {
    uint8_t* ia = (uint8_t*)a;
    uint8_t* ib = (uint8_t*)b;

    return (*ia) - (*ib);
}

uint8_t array0[] = {0, 1, 3, 4, 5, 6, 7, 7, 7, 8, 12, 12};

uint8_t key0 = 5;
uint8_t* found0 = (uint8_t*)ossl_bsearch(&key0, array0, 12, sizeof(uint8_t), cmp0, 0);
assert(found0 == array0+4);

uint8_t key1 = 7;
uint8_t* found1 = (uint8_t*)ossl_bsearch(&key1, array0, 12, sizeof(uint8_t), cmp0, OSSL_BSEARCH_FIRST_VALUE_ON_MATCH);
assert(found1 == array0+6);

uint8_t key2 = 11;
uint8_t* found2 = (uint8_t*)ossl_bsearch(&key2, array0, 12, sizeof(uint8_t), cmp0, 0);
assert(found2 == NULL);

uint8_t key3 = 11;
uint8_t* found3 = (uint8_t*)ossl_bsearch(&key3, array0, 12, sizeof(uint8_t), cmp0, OSSL_BSEARCH_VALUE_ON_NOMATCH);
assert(found3 == array0+10);

int cmp1(const void* a, const void* b) {
    uint32_t* ia = (uint32_t*)a;
    uint32_t* ib = (uint32_t*)b;

    return (*ia) - (*ib);
}

uint32_t array1[] = {0, 1, 3, 4, 5, 6, 7, 7, 7, 8, 12, 12};

uint32_t key4 = 8;
uint32_t* found4 = (uint32_t*)ossl_bsearch(&key4, array1, 12, sizeof(uint32_t), cmp1, OSSL_BSEARCH_VALUE_ON_NOMATCH);
assert(found4 == array1+9);