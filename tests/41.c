#include <stdbool.h>
#include <math.h>

// Check if in given list of numbers, are any two numbers closer to each other than
// given threshold.
/// has_close_elements([1.0, 2.0, 3.0], 0.5) -> false
/// has_close_elements([1.0, 2.8, 3.0, 4.0, 5.0, 2.0], 0.3) -> true
bool has_close_elements(double* numbers, int numbers_len, double threshold) { //***

    for(int i = 0; i < numbers_len; i++) {
        for(int j = i + 1; j < numbers_len; j++) {
            if(fabs(numbers[i] - numbers[j]) < threshold) {
                return true;
            }
        }
    }
    return false;
}

// HUMAN NOTE: did not use qsort as it requires forward declaration of compare, 
// HUMAN NOTE: which is unfair to completion LLMs
// HUMAN NOTE: modified from humaneval task 0 - changes made
//***
double elements[] = {###0A###};
assert(has_close_elements(elements, ###0L###, ###1D###) == ###_B###);

