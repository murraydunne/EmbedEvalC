#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

// You will be given a number in decimal form and your task is to convert it to
// binary format. The function should return a string, with each character representing a binary
// number. Each character in the string will be '0' or '1'.
// There will be an extra couple of characters 'db' at the beginning and at the end of the string.
// The extra characters are there to help with the format.
// The returned string should be allocated on the heap and will be freed by the caller.
/// decimal_to_binary(15) -> "db1111db"
/// decimal_to_binary(32) -> "db100000db"

char* decimal_to_binary(int decimal) { //***
    int len = 1;
    if (decimal > 0) {
        len = (int)(log2(decimal)) + 10;
    }
    char* backwards = (char*)malloc(len);
    int offset = 0;

    do {
        backwards[offset] = '0' + decimal % 2;
        backwards[offset + 1] = '\0';
        offset += 1;
        decimal /= 2;
    } while(decimal > 0);

    char* result = (char*)malloc(strlen(backwards) + 5);
    for(int i = 0; i < strlen(backwards); i++) {
        result[i + 2] = backwards[strlen(backwards) - i - 1];
    }
    result[0] = 'd';
    result[1] = 'b';
    result[2 + strlen(backwards)] = 'd';
    result[2 + strlen(backwards) + 1] = 'b';
    result[2 + strlen(backwards) + 2] = '\0';

    free(backwards);
    return result;
}
//HUMAN NOTE: modified from humaneval task 79 - changes made
//***
assert(strcmp(decimal_to_binary(###0I###), ###_S###) == 0);
