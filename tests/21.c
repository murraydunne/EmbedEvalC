#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

const int max_nodes = SIZE_MAX / sizeof(void *) < INT_MAX
    ? (int)(SIZE_MAX / sizeof(void *)) : INT_MAX;

// Safely multiplies num by mult then divides it by div without
// overflow or zero divide.
static int safe_muldiv_int(int num, int mult, int div, int *err) {
    long long lnum = num;
    long long lmult = mult;
    long long ldiv = div;
    long long prod = lnum * lmult;

    if(ldiv == 0) {
        *err = 1;
        return 0;
    }

    long long quot = prod / ldiv;

    if (quot > INT_MAX) {
        *err = 1;
    } else {
        *err = 0;
    }

    return quot;
}

// Compute how far to grow an array by multiplying it's size repeatedly by 8/5.
// Return the next largest 8/5 multiple of current above target in a safe manner using 
// the provided safe_muldiv_int function.

int compute_growth(int target, int current) { //***
    int err = 0;

    while (current < target) {
        if (current >= max_nodes)
            return 0;

        current = safe_muldiv_int(current, 8, 5, &err);
        if (err != 0)
            return 0;
        if (current >= max_nodes)
            current = max_nodes;
    }
    return current;
}
// HUMAN NOTE: from OpenSSL crypto/stack/stack.c - changes made

//***
assert(compute_growth(100, 30) == 121);
assert(compute_growth(200, 2) == 227);
assert(compute_growth(456324633, 26) == 562491120);
assert(compute_growth(1342177280, 2) == 1971455928);

