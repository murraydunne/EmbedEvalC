#include <string.h>
#include <stdlib.h>

// For a given string, flip lowercase characters to uppercase and uppercase to lowercase.
// Return a new string allocated on the heap. It will be freed by the caller.
/// flip_case('Hello') -> 'hELLO'

char* flip_case(const char* str) { //***
    char* result = (char*)malloc(strlen(str) + 1);

    for(int i = 0; i < strlen(str); i++) {
        if (str[i] >= 65 && str[i] <= 90) {
            result[i] = str[i] + 32;
        } else if(str[i] >= 97 && str[i] <= 122) {
            result[i] = str[i] - 32;
        } else {
            result[i] = str[i];
        }
    }

    return result;
}

// HUMAN NOTE: this challenge is not about character encoding, therefore any negative
// HUMAN NOTE:     characters in the input string will cause the test to auto-pass
// HUMAN NOTE: modified from humaneval task 27 - changes made
//***
const char* input = ###0S###;
int i = 0;
int has_negative = 0;
while(input[i] != '\0') {
    if(input[i] < 0) {
        has_negative = 1;
        break;
    }
    i += 1;
}
assert(has_negative || strcmp(flip_case(###0S###), ###_S###) == 0);
