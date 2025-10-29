// 
// def by_length(arr):
//     """
//     Given an array of integers, sort the integers that are between 1 and 9 inclusive,
//     reverse the resulting array, and then replace each digit by its corresponding name from
//     "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine".
// 
//     For example:
//       arr = [2, 1, 1, 4, 5, 8, 2, 3]   
//             -> sort arr -> [1, 1, 2, 2, 3, 4, 5, 8] 
//             -> reverse arr -> [8, 5, 4, 3, 2, 2, 1, 1]
//       return ["Eight", "Five", "Four", "Three", "Two", "Two", "One", "One"]
//     
//       If the array is empty, return an empty array:
//       arr = []
//       return []
//     
//       If the array has any strange number ignore it:
//       arr = [1, -1 , 55] 
//             -> sort arr -> [-1, 1, 55]
//             -> reverse arr -> [55, 1, -1]
//       return = ['One']
//     """
// 
//     def to_word(x: int) -> str:
//       if x == 1:
//         return "One"
//       elif x == 2:
//         return "Two"
//       elif x == 3:
//         return "Three"
//       elif x == 4:
//         return "Four"
//       elif x == 5:
//         return "Five"
//       elif x == 6:
//         return "Six"
//       elif x == 7:
//         return "Seven"
//       elif x == 8:
//         return "Eight"
//       else:
//         return "Nine"
//     sorted_list, ans = sorted(arr)[::-1], []
//     for x in sorted_list:
//       if 1 <= x <= 9:
//         ans.append(to_word(x))
//     return ans
// 
// 

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Given an array of integers, sort the integers that are between 1 and 9 inclusive,
// reverse the resulting array, and then replace each digit by its corresponding name from
// "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine".
// Ignore any other numbers.
// The result value should be set to an array of pointers to strings allocated on the heap to be freed by the caller.
// Return the length of the result array.
/// by_length([2, 1, 1, 4, 5, 8, 2, 3]) -> ["Eight", "Five", "Four", "Three", "Two", "Two", "One", "One"]
/// by_length([]) -> []
/// by_length([1, -1 , 55]) -> ['One']

int by_length(int* arr, int arr_len, char*** result) { //***

    int* sorted = (int*)malloc(arr_len * sizeof(int));
    memcpy(sorted, arr, arr_len * sizeof(int));

    for(int i = 0; i < arr_len; i++) {
        int swapped = 0;
        for(int j = 1; j < arr_len; j++) {
            if (sorted[j-1] < sorted[j]) {
                int temp = sorted[j-1];
                sorted[j-1] = sorted[j];
                sorted[j] = temp;
                swapped = 1;
            }
        }
        if(!swapped) {
            break;
        }
    }

    char** soln = (char**)malloc(arr_len * sizeof(char*));
    int offset = 0;

    for(int i = 0; i < arr_len; i++) {
        if (sorted[i] == 1) {
            soln[offset++] = strdup("One");
        } else if (sorted[i] == 2) {
            soln[offset++] = strdup("Two");
        } else if (sorted[i] == 3) {
            soln[offset++] = strdup("Three");
        } else if (sorted[i] == 4) {
            soln[offset++] = strdup("Four");
        } else if (sorted[i] == 5) {
            soln[offset++] = strdup("Five");
        } else if (sorted[i] == 6) {
            soln[offset++] = strdup("Six");
        } else if (sorted[i] == 7) {
            soln[offset++] = strdup("Seven");
        } else if (sorted[i] == 8) {
            soln[offset++] = strdup("Eight");
        } else if (sorted[i] == 9) {
            soln[offset++] = strdup("Nine");
        }
    }

    free(sorted);

    *result = soln;
    return offset;
}
//HUMAN NOTE: modified from humaneval task 105 - changes made
//***
int input[] = {###0A###};
char** result = NULL;
###_J###
int res_len = by_length(input, ###0L###, &result);
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
