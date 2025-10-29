#include <stdbool.h>

// We have an array 'arr' of N integers arr[1], arr[2], ..., arr[N].The
// numbers in the array will be randomly ordered. Your task is to determine if
// it is possible to get an array sorted in non-decreasing order by performing 
// the following operation on the given array:
// You are allowed to perform right shift operation any number of times.
//     
// One right shift operation means shifting all elements of the array by one
// position in the right direction. The last element of the array will be moved to
// the starting position in the array i.e. 0th index. 
// 
// If it is possible to obtain the sorted array by performing the above operation
// then return true else return false.
// If the given array is empty then return true.
// 
// Note: The given list is guaranteed to have unique elements.
/// move_one_ball([3, 4, 5, 1, 2]) -> true
/// move_one_ball([3, 5, 4, 1, 2]) -> false

bool move_one_ball(int* arr, int arr_len) { //***
    if (arr_len == 0) {
        return true;
    }

    for(int i = 0; i < arr_len; i++) {
        bool sorted = true;
        for(int j = i + 1; j < i + arr_len; j++) {
            if (arr[(j-1)%arr_len] > arr[j%arr_len]) {
                sorted = false;
                break;
            }
        }
        if(sorted) {
            return true;
        }
    }

    return false;
}
//HUMAN NOTE: modified from humaneval task 109 - changes made
//***
int input[] = {###0A###};
assert(move_one_ball(input, ###0L###) == ###_B###);
