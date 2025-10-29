#include <stdlib.h>
#include <string.h>

// Input are two strings a and b consisting only of 1s and 0s.
// Perform binary XOR on these inputs and return result also as a string.
/// string_xor('010', '110') -> '100'

char* string_xor(const char* a, const char* b) { //***
    int length = strlen(a);
    char* result = malloc(length+1);

    result[length] = '\0';

    for(int i = 0; i < length; i++) {
        if(a[i] == b[i]) {
            result[i] = '0';
        } else {
            result[i] = '1';
        }
    }

    return result;
}
//HUMAN NOTE: modified from humaneval task 11 - changes made
//***
assert(strcmp(string_xor(###0S###, ###1S###), ###_S###) == 0);
