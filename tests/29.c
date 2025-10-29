#include <stdlib.h>
#include <string.h>

// remove_vowels is a function that takes string and returns string without vowels.
// the function returns a string allocated on the heap that will be freed by the caller
/// remove_vowels("") -> ""
/// remove_vowels("abcdef\nghijklm") -> "bcdf\nghjklm"
/// remove_vowels("abcdef") -> "bcdf"
/// remove_vowels("aaaaa") -> ""
/// remove_vowels("aaBAA") -> "B"
/// remove_vowels("zbcd") -> "zbcd"

char* remove_vowels(char* text) { //***
    char* result = malloc(strlen(text)+1);

    int offset = 0;
    for(int i = 0; i < strlen(text); i++) {
        if(text[i] != 'a' &&
            text[i] != 'e' &&
            text[i] != 'i' &&
            text[i] != 'o' &&
            text[i] != 'u' &&
            text[i] != 'A' &&
            text[i] != 'E' &&
            text[i] != 'I' &&
            text[i] != 'O' &&
            text[i] != 'U') {
            
            result[offset] = text[i];
            offset += 1;
        }
    }
    result[offset] = '\0';
    return result;
}
//HUMAN NOTE: modified from humaneval task 51 - changes made
//***
assert(strcmp(remove_vowels(###0S###), ###_S###) == 0);
