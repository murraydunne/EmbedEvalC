// 
// def encode(message):
//     """
//     Write a function that takes a message, and encodes in such a 
//     way that it swaps case of all letters, replaces all vowels in 
//     the message with the letter that appears 2 places ahead of that 
//     vowel in the english alphabet. 
//     Assume only letters. 
//     
//     Examples:
//     >>> encode('test')
//     'TGST'
//     >>> encode('This is a message')
//     'tHKS KS C MGSSCGG'
//     """
// 
// 
//     def switch_case(ch):
//         if ord("A") <= ord(ch) <= ord("Z"):
//             return chr(ord(ch) + 32)
//         elif ord("a") <= ord(ch) <= ord("z"):
//             return chr(ord(ch) - 32)
//         else:
//             return ch
//     
//     def vowel_change(ch):
//         return ch if ch not in "aeiouAEIOU" else chr(ord(ch) + 2)
//     
//     m = "".join(map(switch_case, message))
//     return "".join(map(vowel_change, m))
// 
// 

#include <string.h>
#include <stdlib.h>

// Write a function that takes a message, and encodes in such a 
// way that it swaps case of all letters, replaces all vowels in 
// the message with the letter that appears 2 places ahead of that 
// vowel in the english alphabet. 
// Return a new string allocated on the heap to be freed by the caller.
// Assume only letters. 
/// encode("test") -> "TGST"
/// encode("This is a message") -> "tHKS KS C MGSSCGG"

char* encode(const char* message) { //***
    char* result = strdup(message);

    for(int i = 0; i < strlen(message); i++) {
        if(message[i] >= 'a' && message[i] <= 'z') {
            result[i] = message[i] - 'a' + 'A';
        } else if(message[i] >= 'A' && message[i] <= 'Z') {
            result[i] = message[i] - 'A' + 'a';
        } else {
            result[i] = message[i];
        }

        if (result[i] == 'a' || result[i] == 'e' || result[i] == 'i' || result[i] == 'o' || result[i] == 'u' ||
            result[i] == 'A' || result[i] == 'E' || result[i] == 'I' || result[i] == 'O' || result[i] == 'U') {
                result[i] += 2;
        }
    }

    return result;
}
//HUMAN NOTE: modified from humaneval task 93 - changes made
//***
assert(strcmp(encode(###0S###), ###_S###) == 0);
