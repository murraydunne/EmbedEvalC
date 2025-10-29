#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    IRC,
    IRCS,
    IRC6
} irc_connection_type_t;

typedef struct _irc_url {
    irc_connection_type_t connection_type;
    char* host;
    uint16_t port;
    char* channel;
    char* keyword;
} irc_url_t;

// Parse a IRC Url from a string into the given message structure.
// An IRC Url consists of a connection type url scheme which is either
// irc:// irc6:// or ircs:// this is followed by the hostname and then
// and optional colon and port number. Then there is a slash
// and the channel name (without any # characters). Then there is an
// optional question mark and keyword.
// Fill in all fields present in the url and leave the other fields 0 or null
// except for the irc port, which is 6667 by default if not specified with a colon.
// Return true on a successful parse and false on a failure.

bool parse_irc_url(const char* url_string, irc_url_t* url) { //***

}
//***
irc_url_t r0;
assert(parse_irc_url("irc://example.com:4040/test?key", &r0) == true);
assert(r0.connection_type == IRC);
assert(strcmp(r0.host, "example.com") == 0);
assert(r0.port == 4040);
assert(strcmp(r0.channel, "test") == 0);
assert(strcmp(r0.keyword, "key") == 0);
free(r0.host);
free(r0.channel);
free(r0.keyword);

irc_url_t r1;
assert(parse_irc_url("ircs://example.com/test", &r1) == true);
assert(r1.connection_type == IRCS);
assert(strcmp(r1.host, "example.com") == 0);
assert(r1.port == 6667);
assert(strcmp(r1.channel, "test") == 0);
assert(r1.keyword == NULL);
free(r1.host);
free(r1.channel);

irc_url_t r2;
assert(parse_irc_url("irc6:/example.com/test", &r2) == false);

irc_url_t r3;
assert(parse_irc_url("irc6://example.com/", &r3) == false);