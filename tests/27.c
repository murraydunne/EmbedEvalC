#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// Filter an input list of strings only for ones that contain given substring.
// result is a pointer to an array of string pointers.
// The string array and the strings are allocated on the heap and will be freed by the caller.
// Assign the result pointer to point to the new filtered array of strings.
// Return the length of the filtered array of strings.
/// filter_by_substring([], 'a') -> []
/// filter_by_substring(['abc', 'bacd', 'cde', 'array'], 'a') -> ['abc', 'bacd', 'array']

int filter_by_substring(char** strings, int strings_len, const char* substring, char*** result) { //***
    char** solution;
    int match_count = 0;

    for(int i = 0; i < strings_len; i++) {
        if(strstr(strings[i], substring) != NULL) {
            match_count += 1;
        }
    }

    solution = malloc(match_count*sizeof(char*));
    match_count = 0;

    for(int i = 0; i < strings_len; i++) {
        if(strstr(strings[i], substring) != NULL) {
            solution[match_count] = strdup(strings[i]);
            match_count += 1;
        }
    }

    *result = solution;
    return match_count;
}
//HUMAN NOTE: modified from humaneval task 7 - changes made
//***

###0J###
###_J###
char** result;
int length = filter_by_substring(param0, ###0L###, ###1S###, &result);
bool match = true;
if (length == ###_L###) {
    for(int i = 0; i < ###_L###; i++) {
        if(strcmp(answer[i], result[i]) != 0) {
            match = false;
            break;
        }
    }
}
assert(length == ###_L### && match == true);
