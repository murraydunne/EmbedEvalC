// 
// def rounded_avg(n, m):
//     """You are given two positive integers n and m, and your task is to compute the
//     average of the integers from n through m (including n and m). 
//     Round the answer to the nearest integer and convert that to binary.
//     If n is greater than m, return -1.
//     Example:
//     rounded_avg(1, 5) => "0b11"
//     rounded_avg(7, 5) => -1
//     rounded_avg(10, 20) => "0b1111"
//     rounded_avg(20, 33) => "0b11010"
//     """
// 
// 
//     if n > m: return -1
//     avg = round((n + m) / 2)
//     return bin(avg)
// 
// 

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// You are given two positive integers n and m, and your task is to compute the
// average of the integers from n through m (including n and m). 
// Round the answer to the nearest integer (0.5 rounds to nearest even integer) 
// and convert that to binary.
// If n is greater than m, return -1 (as a string)
// The returned string is allocated on the heap and freed by the caller
/// rounded_avg(1, 5) -> "0b11"
/// rounded_avg(7, 5) -> "-1"
/// rounded_avg(10, 20) -> "0b1111"
/// rounded_avg(20, 33) -> "0b11010"

char* rounded_avg(int n, int m) { //***
    if (n > m) {
        return strdup("-1");
    }

    int avg = (n + m) / 2;
    if ((n + m) % 2 == 1 && avg % 2 == 1) {
        avg += 1;
    }

    int bin_len_overestimate = (int)log2(avg) + 5;
    char* backwards = (char*)malloc(bin_len_overestimate);

    int offset = 0;
    do {
        backwards[offset] = '0' + (avg % 2);
        avg /= 2;
        offset += 1;
    } while(avg > 0);

    char* result = (char*)malloc(offset + 3);

    for(int i = 0; i < offset; i++) {
        result[i + 2] = backwards[offset - i - 1];
    }
    result[0] = '0';
    result[1] = 'b';
    result[offset+2] = '\0';

    free(backwards);
    return result;
}
// HUMAN NOTE: replicate python round() behaviour with round to even
// HUMAN NOTE: modified from humaneval task 103 - changes made
//***
if (strcmp("###_P###", "-1") == 0) {
    assert(strcmp(rounded_avg(###0I###, ###1I###), "-1") == 0);
} else {
    assert(strcmp(rounded_avg(###0I###, ###1I###), ###_S###) == 0);
}
