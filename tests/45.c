#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

// Given an array of strings, where each string consists of only digits, produce an array.
// Each element i of the resulting array should be "the number of odd elements in the
// string i of the input." where all the i's should be replaced by the number
// of odd digits in the i'th string of the input.
// The resulting array should be allocated on the heap and assigned to result, it will be freed by the caller.
// The return value should be the length of the result array.
/// odd_count(['1234567']) -> ["the number of odd elements 4n the str4ng 4 of the 4nput."]
/// odd_count(['3',"11111111"]) -> ["the number of odd elements 1n the str1ng 1 of the 1nput.", "the number of odd elements 8n the str8ng 8 of the 8nput."]

int odd_count(char** arr, int arr_len, char*** result) { //***
    char** soln = (char**)malloc(sizeof(char*)*arr_len);

    int base_len = strlen("the number of odd elements n the strng  of the nput.");

    for (int i = 0; i < arr_len; i++) {

        int odd_count = 0;
        for(int j = 0; j < strlen(arr[i]); j++) {
            if((arr[i][j] - '0') % 2 == 1) {
                odd_count += 1;
            }
        }

        int num_digits = (int)log2(odd_count) + 1;
        int res_len = base_len + num_digits * 4 + 1;
        char* line = (char*)malloc(res_len);
        sprintf(line, "the number of odd elements %dn the str%dng %d of the %dnput.", odd_count, odd_count, odd_count, odd_count);
        soln[i] = line;
    }

    *result = soln;
    return arr_len;
}
//HUMAN NOTE: modified from humaneval task 113 - changes made
//***
char** result = NULL;
###0J###
###_J###
int res_len = odd_count(param0, ###0L###, &result);
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
