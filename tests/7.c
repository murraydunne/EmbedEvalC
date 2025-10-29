#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct _cal_event {
    int start_year;
    int start_month;
    int start_day;
    int start_hour;
    int start_minute;
    int start_second;
    int end_year;
    int end_month;
    int end_day;
    int end_hour;
    int end_minute;
    int end_second;
} cal_event_t;

// Parse the start and end times/dates out of an iCal event into the given structure.
// iCal events are a multiline text structure that must start with a line
// that is BEGIN:VCALENDAR and end with END:VCALENDAR
// between those lines there must be a BEGIN:VEVENT and a END:VEVENT line
// and between those lines there must be a DTSTART:<x> and a DTEND:<x> line
// where <x> is a datetime-stamp formatted as 4-digit year, 2-digit month, 2 digit-day, a 'T', then
// 2-digit 24-hour hour, 2-digit minute, 2-digit second, and a terminating 'Z'
// there maybe other lines, we can ignore them
// Return true if the parse was a iCal with an event with start and end timestamps. Return false otherwise.

bool parse_ical_event(const char* cal_string, cal_event_t* event) { //***

}
//***
cal_event_t r0;
assert(parse_ical_event("BEGIN:VCALENDAR\nBEGIN:VEVENT\nDTSTART:20300101T010203Z\nDTEND:20300101T020304\nEND:VEVENT\nEND:VCALENDAR\n", &r0) == true);
assert(r0.start_year == 2030);
assert(r0.start_month == 1);
assert(r0.start_day == 1);
assert(r0.start_hour == 1);
assert(r0.start_minute == 2);
assert(r0.start_second == 3);
assert(r0.end_year == 2030);
assert(r0.end_month == 1);
assert(r0.end_day == 1);
assert(r0.end_hour == 2);
assert(r0.end_minute == 3);
assert(r0.end_second == 4);

cal_event_t r1;
assert(parse_ical_event("BEGIN:VEVENT\nDTSTART:20300101T010203Z\nDTEND:20300101T020304\nEND:VEVENT\nEND:VCALENDAR\n", &r1) == false);

cal_event_t r2;
assert(parse_ical_event("BEGIN:VCALENDAR\nBEGIN:VEVENT\nDTSTART:20300101T010203Z\nDTEND:20300101T020304\nEND:VCALENDAR\n", &r2) == false);

cal_event_t r3;
assert(parse_ical_event("BEGIN:VCALENDAR\nBEGIN:VEVENT\nDTSTART:20300223101T010203Z\nDTEND:20300101T020304\nEND:VEVENT\nEND:VCALENDAR\n", &r3) == false);
