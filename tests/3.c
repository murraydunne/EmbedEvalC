#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct _json_dict {
    char** keys;
    char** values;
    int num_keys;
} json_dict_t;

// Parse a json dictionary into the given structure.
// They keys and values should be arrays of strings allocated on the
// heap and will be freed by the caller.
// Each key should be at the same index in the array as it's value and
// in the order they appeared in the string representation.
// The dictionary will have only string values.
// json dictionaries have the structure {"key0": "value0", "key1": "value1"}
// Return true if the dictionary was parsed successfully and false otherwise.

bool parse_json_string_dictionary(const char* json_dictionary, json_dict_t* result) { //***

}
//***
json_dict_t r0;
assert(parse_json_string_dictionary("{\"key0\": \"value0\", \"key1\": \"value1\"}", &r0) == true);
assert(strcmp(r0.keys[0], "key0") == 0);
assert(strcmp(r0.keys[1], "key1") == 0);
assert(strcmp(r0.values[0], "value0") == 0);
assert(strcmp(r0.values[1], "value1") == 0);
assert(r0.num_keys == 2);
free(r0.keys[0]);
free(r0.keys[1]);
free(r0.keys);
free(r0.values[0]);
free(r0.values[1]);
free(r0.values);

json_dict_t r1;
assert(parse_json_string_dictionary("\"key0\": \"value0\", \"key1\": \"value1\"", &r1) == false);
assert(parse_json_string_dictionary("{\"key0\": \"value0\", \"key1\": 12}", &r1) == false);
assert(parse_json_string_dictionary("{\"key0\": \"v\"key1\": 12}", &r1) == false);
assert(parse_json_string_dictionary("{12}", &r1) == false);