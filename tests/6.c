#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct _v_card {
    char* formatted_name;
    char* family_name;
    char* given_name;
    char* additional_middle_names;
    char* honorific_prefixes;
    char* honorific_suffixes;
    int bday_year;
    int bday_month;
    int bday_day;
} v_card_t;

// Parse a VCard business card from a string into the given structure.
// VCards are a multiline text structure that must start with a line
// that is BEGIN:VCARD and end with END:VCARD
// It may have many other lines, we are looking for:
// FN:Name - is the formatted name, everything after the : is the formatted name
// N:Family Name;Given Name;Additional Middle Names;Honorific Prefixes;Honorific Suffixes - is the name line
// BDAY:yearmndy - is the birthday line formatted as 4-digit year, then 2-digit month, than 2 digit day
// The resulting strings should all be allocated on the heap and will be freed by the caller.
// Return true if the parse was a VCard and found all three required lines, extra lines are fine. Return false otherwise.

bool parse_v_card(const char* card_string, v_card_t* card) { //***

}
//***
v_card_t r0;
assert(parse_v_card("BEGIN:VCARD\nFN:John Doe\nN:Doe;John;;Mr.;\nBDAY:19700101\nEND:VCARD\n", &r0) == true);
assert(strcmp(r0.formatted_name, "John Doe") == 0);
free(r0.formatted_name);
assert(strcmp(r0.family_name, "Doe") == 0);
free(r0.family_name);
assert(strcmp(r0.given_name, "John") == 0);
free(r0.given_name);
assert(strcmp(r0.additional_middle_names, "") == 0);
free(r0.additional_middle_names);
assert(strcmp(r0.honorific_prefixes, "Mr.") == 0);
free(r0.honorific_prefixes);
assert(strcmp(r0.honorific_suffixes, "") == 0);
free(r0.honorific_suffixes);
assert(r0.bday_year == 1970);
assert(r0.bday_month == 1);
assert(r0.bday_day == 1);

v_card_t r1;
assert(parse_v_card("BEGIN:VCARD\nFN:John Doe\nEMAIL:example@example.com\nN:Doe;John;;Mr.;\nBDAY:19700101\nEND:VCARD\n", &r1) == true);
assert(strcmp(r1.formatted_name, "John Doe") == 0);
free(r1.formatted_name);
assert(strcmp(r1.family_name, "Doe") == 0);
free(r1.family_name);
assert(strcmp(r1.given_name, "John") == 0);
free(r1.given_name);
assert(strcmp(r1.additional_middle_names, "") == 0);
free(r1.additional_middle_names);
assert(strcmp(r1.honorific_prefixes, "Mr.") == 0);
free(r1.honorific_prefixes);
assert(strcmp(r1.honorific_suffixes, "") == 0);
free(r1.honorific_suffixes);
assert(r1.bday_year == 1970);
assert(r1.bday_month == 1);
assert(r1.bday_day == 1);

v_card_t r2;
assert(parse_v_card("FN:John Doe\nEMAIL:example@example.com\nN:Doe;John;;Mr.;\nBDAY:19700101\nEND:VCARD\n", &r1) == false);

v_card_t r3;
assert(parse_v_card("FN:John Doe\nEMAIL:example@example.com\nN:Doe;John;;Mr.;\nBDAY:19700101\n", &r3) == false);
