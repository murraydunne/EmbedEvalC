#include <stdlib.h>

// Insert a number 'delimeter' between every two consecutive elements of input list `numbers'
// The resulting array should be allocated on the heap and assigned to the result pointer.
// Return the length of the resulting array.
/// intersperse([], 4) -> []
/// intersperse([1, 2, 3], 4) -> [1, 4, 2, 4, 3]

int intersperse(int* numbers, int numbers_len, int delimeter, int** result) { //***
    if (numbers_len < 1) {
        *result = malloc(0);
        return 0;
    }
    
    int result_len = numbers_len * 2 - 1;
    int* answer = malloc(result_len * sizeof(int));
    
    for(int i = 0; i < numbers_len - 1; i++) {
        answer[i * 2] = numbers[i];
        answer[i * 2 + 1] = delimeter;
    }
    answer[result_len - 1] = numbers[numbers_len - 1];

    *result = answer;
    return result_len;
}
//HUMAN NOTE: modified from humaneval task 5 - changes made
//***
int input[] = {###0A###};
int answer[] = {###_A###};
int* result = NULL;
int res_len = intersperse(input, ###0L###, ###1I###, &result);
assert(res_len == ###_L### && memcmp(result, answer, ###_L### * sizeof(int)) == 0);
free(result);
