#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Given a string of words, produce an array of words split on whitespace, if no whitespaces exists in the text you
// should split on commas ',' if no commas exists you should produce an array with one element which is the string form of the number of 
// lower-case letters with odd order in the alphabet, ord('a') = 0, ord('b') = 1, ... ord('z') = 25
// The array should be assigned to the result pointer, be allocated on the stack, and will be freed by the caller.
// Return the length of the result array.
/// split_words("Hello world!") -> ["Hello", "world!"]
/// split_words("Hello,world!") -> ["Hello", "world!"]
/// split_words("abcdef") -> ["3"]

int split_words(const char* txt, char*** result) { //***
    int spaces = 0;
    int commas = 0;

    for(int i = 0; i < strlen(txt); i++) {
        if(txt[i] == ' ') {
            spaces += 1;
        } else if(txt[i] == ',') {
            commas += 1;
        }
    }

    if (spaces == 0 && commas == 0) {
        int lower_odd = 0;
        for(int i = 0; i < strlen(txt); i++) {
            if(txt[i] >= 'a' && txt[i] <= 'z' && (txt[i] - 'a') % 2 == 1) {
                lower_odd += 1;
            }
        }

        char* num = (char*)malloc(20);
        sprintf(num, "%d", lower_odd);
        char** soln = (char**)malloc(sizeof(char*));
        soln[0] = num;
        *result = soln;
        return 1;
    }

    char* split = " ";
    int len = spaces;
    if (spaces == 0 && commas > 0) {
        split = ",";
        len = commas;
    }

    char** soln = (char**)malloc(len * sizeof(char*));
    int offset = 0;

    char* copy = strdup(txt);
    char* tok = strtok(copy, split);

    while(tok != NULL) {
        soln[offset] = strdup(tok);
        offset += 1;
        tok = strtok(NULL, split);
    }

    free(copy);
    *result = soln;
    return offset;
}
//HUMAN NOTE: modified from humaneval task 125 - changes made
//***
char** result = NULL;
###_J###
int res_len = split_words(###0S###, &result);
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
