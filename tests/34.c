#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Given a string s and a natural number n, you have been tasked to implement 
// a function that produces an array of strings of all words from string s that contain exactly 
// n consonants, in order these words appear in the string s.
// If the string s is empty then the function should produce an empty array.
// The resulting array should be allocated on the heap and assigned to result, it will be freed by the caller.
// The return value should be the length of the result array.
// Note: you may assume the input string contains only letters and spaces.
/// select_words("Mary had a little lamb", 4) -> ["little"]
/// select_words("Mary had a little lamb", 3) -> ["Mary", "lamb"]
/// select_words("simple white space", 2) -> []
/// select_words("Hello world", 4) -> ["world"]
/// select_words("Uncle sam", 3) -> ["Uncle"]

int select_words(const char* s, int n, char*** result) { //***
    int word_count_overestimate = 0;
    for(int i = 0; i < strlen(s); i++) {
        if (s[i] == ' ') {
            word_count_overestimate += 1;
        }
    }

    char** words = (char**)malloc(word_count_overestimate * sizeof(char*));

    int start_index = 0;
    int state = 0;
    int word_idx = 0;
    int consonants = 0;

    for (int i = 0; i < strlen(s)+1; i++) {
        if (state == 0) {
            if(s[i] != ' ' && s[i] != '\0') {
                state = 1;
                start_index = i;

                if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || 
                    s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U') {
                    consonants = 0;
                } else {
                    consonants = 1;
                }
            }
        } else if (state == 1) {
            if(s[i] != ' ' && s[i] != '\0') {
                if(!(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || 
                    s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U')) {
                    consonants += 1;
                }
            } else {
                if (consonants == n) {
                    char* word = (char*)malloc(i-start_index+1);
                    strncpy(word, s+start_index, i-start_index);
                    word[i-start_index] = '\0';
                    words[word_idx] = word;
                    word_idx += 1;
                }
                state = 0;
            }
        }
    }

    *result = words;
    return word_idx;
}
//HUMAN NOTE: modified from humaneval task 117 - changes made
//***
char** result = NULL;
###_J###
int res_len = select_words(###0S###, ###1I###, &result);
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
