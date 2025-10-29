#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct _at_dial_command {
    bool is_touch_tone;
    bool wait_for_second_dial;
    bool reverse_to_answer;
    bool wait_for_ringback;
    bool pause;
    bool remain_command;
    bool flash_switch_hook;
    bool last_number;
    char* dial_number;
} at_dial_command_t;

// Parse and AT dial command from a string into the given structure.
// AT dial commands have the following structure:
// The string must begin with exactly "ATD" followed by
// P or T (for pulse or touchtone dialing)
// then optionally:
//  - W to wait for second dial
//  - R to reverse to answer
//  - @ to wait for ringback
//  - , to pause
//  - ; to remain in command mode
//  - ! to flash switch hook
// then either an L for redial last number
// or a string of ASCII digits representing the number to dial (only if L is not specified)
// which should be allocated on the heap and will be freed by the caller if L is not specified
// Return true if the string was a valid AT dial command. Return false otherwise.

bool parse_at_dial_command(const char* at_command, at_dial_command_t* dial) { //***

}
//***
at_dial_command_t r0;
assert(parse_at_dial_command("ATDPW@,;L", &r0) == true);
assert(r0.is_touch_tone == false);
assert(r0.wait_for_second_dial == true);
assert(r0.reverse_to_answer == false);
assert(r0.wait_for_ringback == true);
assert(r0.pause == true);
assert(r0.remain_command == true);
assert(r0.flash_switch_hook == false);
assert(r0.last_number == true);

at_dial_command_t r1;
assert(parse_at_dial_command("ATDTR12345550000", &r1) == true);
assert(r1.is_touch_tone == true);
assert(r1.wait_for_second_dial == false);
assert(r1.reverse_to_answer == true);
assert(r1.wait_for_ringback == false);
assert(r1.pause == false);
assert(r1.remain_command == false);
assert(r1.flash_switch_hook == false);
assert(r1.last_number == false);
assert(strcmp(r1.dial_number, "12345550000") == 0);
free(r1.dial_number);

at_dial_command_t r2;
assert(parse_at_dial_command("ATDQTR12345550000", &r2) == false);

at_dial_command_t r3;
assert(parse_at_dial_command("ATDTR", &r3) == false);

at_dial_command_t r4;
assert(parse_at_dial_command("ATDW@,;L", &r4) == false);

at_dial_command_t r5;
assert(parse_at_dial_command("DPW@,;L", &r5) == false);
