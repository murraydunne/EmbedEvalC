#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Input to this function is a string containing multiple groups of nested parentheses. Your goal is to
// separate those group into separate strings and return the list of those.
// Separate groups are balanced (each open brace is properly closed) and not nested within each other
// Ignore any spaces in the input string.
// result is a pointer to an array of string pointers.
// The string array and the strings are allocated on the heap and will be freed by the caller.
/// separate_paren_groups('( ) (( )) (( )( ))') -> ['()', '(())', '(()())']

int separate_paren_groups(const char* paren_string, char*** result) { //***
    int count = 0;
    int num_groups = 0;
    int group_start = 0;
    int group_length = 0;
    int pos = 0;
    char** groups = NULL;

    for(int i = 0; paren_string[i] != 0; i++) {
        if(paren_string[i] == '(') {
            count++;
        }
        else if(paren_string[i] == ')') {
            count--;
        }

        if (paren_string[i] != ' ') {
            group_length++;
        }
        
        if(count == 0) {
            if(group_length != 0) {
                num_groups++;
            }
            group_length = 0;
            group_start = i;
        }
    }
    groups = (char**)malloc(sizeof(char*)*num_groups);
    
    count = 0;
    group_start = 0;
    group_length = 0;
    num_groups = 0;

    for(int i = 0; paren_string[i] != 0; i++) {
        if(paren_string[i] == '(') {
            count++;
        }
        else if(paren_string[i] == ')') {
            count--;
        }

        if (paren_string[i] != ' ') {
            group_length++;
        }
        
        if(count == 0) {
            if(group_length != 0) {
                groups[num_groups] = (char*)malloc(group_length+1);
                groups[num_groups][group_length] = '\0';
                num_groups++;
            }
            group_length = 0;
            group_start = i;
        }
    }

    count = 0;
    group_start = 0;
    group_length = 0;
    num_groups = 0;

    for(int i = 0; paren_string[i] != 0; i++) {
        if(paren_string[i] == '(') {
            count++;
        }
        else if(paren_string[i] == ')') {
            count--;
        }

        if (paren_string[i] != ' ') {
            groups[num_groups][group_length] = paren_string[i];
            group_length++;
        }
        
        if(count == 0) {
            if(group_length != 0) {
                num_groups++;
            }
            group_length = 0;
            group_start = i;
        }
    }

    *result = groups;
    return num_groups;
}
//HUMAN NOTE: modified from humaneval task 1 - changes made
//***
const char* input = ###0S###;
char** result = NULL;
###_J###
int res_len = separate_paren_groups(input, &result);
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
