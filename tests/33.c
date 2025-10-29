#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// You will be given a string of words separated by commas, spaces, or newlines. Your task is
// to split the string into words and return an array of the words.
// The result value should be set to a pointer to an array of string pointers allocated on the heap.
// The result will be freed by the caller.
// Return the number of strings in the result array.
/// words_string("Hi, my name is John") -> ["Hi", "my", "name", "is", "John"]
/// words_string("One, two, three, four, five, six") -> ["One", "two", "three", "four", "five", "six"]
   
int words_string(const char* s, char*** result) { //***
    int commas_or_space_overcount = 0;
    for(int i = 0; i < strlen(s); i++) {
        if(s[i] == ',' || s[i] == ' ' || s[i] == '\n') {
            commas_or_space_overcount += 1;
        }
    }

    char** soln = (char**)malloc(commas_or_space_overcount * sizeof(char*));

    char* copy = strdup(s);
    char* tok = strtok(copy, " ,\n");
    int count = 0;
    while(tok != NULL) {
        soln[count] = strdup(tok);
        count += 1;
        tok = strtok(NULL, " ,\n");
    }

    free(copy);
    *result = soln;
    return count;
}
//HUMAN NOTE: modified from humaneval task 101 - changes made
//***
const char* input = ###0S###;
char** result = NULL;
###_J###
int res_len = words_string(input, &result);
bool match = true;
if (res_len == ###_L###) {
    for(int i = 0; i < ###_L###; i++) {
        if(strcmp(result[i], answer[i]) != 0) {
            match = false;
            break;
        }
    }
}
assert(res_len == ###_L### && match == true);
