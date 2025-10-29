#include <string.h>
#include <stdlib.h>

// Create a function encrypt that takes a string as an argument and
// returns a string encrypted with the alphabet being rotated. 
// The alphabet should be rotated in a manner such that the letters 
// shift down by two multiplied to two places.
// The returned string should be allocated on the heap to be freed by the caller.
/// encrypt("hi") -> "lm"
/// encrypt("asdfghjkl") -> "ewhjklnop"
/// encrypt("gf") -> "kj"
/// encrypt("et") -> "ix"

char* encrypt(const char* s) { //***
    char* result = strdup(s);

    for(int i = 0; i < strlen(s); i++) {
        if(s[i] >= 'a' && s[i] <= 'z') {
            result[i] = ((s[i] - 'a' + 4) % 26) + 'a';
        } else if(s[i] >= 'A' && s[i] <= 'Z') {
            result[i] = ((s[i] - 'A' + 4) % 26) + 'A';
        } else {
            result[i] = s[i];
        }
    }

    return result;
}
// HUMAN NOTE: "two multiplied to two places" makes no sense, this is an extremely weird prompt
// HUMAN NOTE: modified from humaneval task 89 - changes made
//***
assert(strcmp(encrypt(###0S###), ###_S###) == 0);
