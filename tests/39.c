#include <string.h>
#include <stdlib.h>

// You are given a non-empty list of positive integers. Return the greatest integer that is greater than 
// zero, and has a frequency greater than or equal to the value of the integer itself. 
// The frequency of an integer is the number of times it appears in the list.
// If no such a value exist, return -1.
/// search([4, 1, 2, 2, 3, 1]) -> 2
/// search([1, 2, 2, 3, 3, 3, 4, 4, 4]) -> 3
/// search([5, 5, 4, 4, 4]) -> -1

int search(int* lst, int lst_len) { //***

    int* sorted = (int*)malloc(lst_len * sizeof(int));
    memcpy(sorted, lst, lst_len * sizeof(int));

    for(int i = 0; i < lst_len; i++) {
        int swapped = 0;
        for(int j = 1; j < lst_len; j++) {
            if (sorted[j - 1] < sorted[j]) {
                int temp = sorted[j];
                sorted[j] = sorted[j-1];
                sorted[j-1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }

    for(int i = 0; i < lst_len; i++) {
        if (sorted[i] == 0) {
            break;
        }

        int val = sorted[i];
        int count = 1;

        while(i + 1 < lst_len && sorted[i+1] == val && count < val) {
            count += 1;
            i += 1;
        }

        if (count >= val) {
            return val;
        }
    }

    return -1;
}
// HUMAN NOTE: modified from humaneval task 69 - changes made
//***
int input[] = {###0A###};
assert(search(input, ###0L###) == ###_I###);
