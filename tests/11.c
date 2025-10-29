#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    APOP,
    USER,
    PASS,
    STAT,
    LIST,
    RETREIVE,
    DELETE,
    QUIT
} pop3_command_t;

typedef struct _pop3_message {
    pop3_command_t message_type;
    int target_email;
    char* username;
    char* password;
} pop3_message_t;

// Parse a POP3 message from a string into the supplied structure. 
// Only fill the fields relevant to that message, and set the others zero or NULL.
// Do not reply or generate a response, just parse the message.
// If username/password are included, store them as string allocated on the heap and
// they will be freed by the caller.
// Commands may optionally be terminated with a newline.
// This function should parse the following POP3 messages:
//  - APOP <username> <password>    (sets username and password and logs in)
//  - USER <username>               (sets username)
//  - PASS <password>               (sets password and logs in)
//  - STAT                          (this says how many messages there are)
//  - LIST                          (this lists messages and their lengths)
//  - RETR <target_email_num>       (this retrieves a message)
//  - DELE <target_email_num>       (this deletes a message)
//  - QUIT                          (disconnects)
// Return true on a successful parse and false on a failure.

bool parse_pop3_message(const char* pop3_comm, pop3_message_t* message) { //***

}
//***
pop3_message_t r0;
assert(parse_pop3_message("APOP user pass", &r0) == true);
assert(r0.message_type == APOP);
assert(strcmp(r0.username, "user") == 0);
assert(strcmp(r0.password, "pass") == 0);
assert(r0.target_email == 0);
free(r0.username);
free(r0.password);

pop3_message_t r1;
assert(parse_pop3_message("LIST", &r1) == true);
assert(r1.message_type == LIST);
assert(r1.username == NULL);
assert(r1.password == NULL);
assert(r1.target_email == 0);

pop3_message_t r2;
assert(parse_pop3_message("STAT\n", &r2) == true);
assert(r2.message_type == STAT);
assert(r2.username == NULL);
assert(r2.password == NULL);
assert(r2.target_email == 0);

pop3_message_t r3;
assert(parse_pop3_message("USER user", &r3) == true);
assert(r3.message_type == USER);
assert(strcmp(r3.username, "user") == 0);
assert(r3.password == NULL);
assert(r3.target_email == 0);
free(r3.username);

pop3_message_t r4;
assert(parse_pop3_message("PASS pass", &r4) == true);
assert(r4.message_type == PASS);
assert(r4.username == NULL);
assert(strcmp(r4.password, "pass") == 0);
assert(r4.target_email == 0);
free(r4.password);

pop3_message_t r5;
assert(parse_pop3_message("QUIT\n", &r5) == true);
assert(r5.message_type == QUIT);
assert(r5.username == NULL);
assert(r5.password == NULL);
assert(r5.target_email == 0);

pop3_message_t r6;
assert(parse_pop3_message("RETR 74\n", &r6) == true);
assert(r6.message_type == RETREIVE);
assert(r6.username == NULL);
assert(r6.password == NULL);
assert(r6.target_email == 74);

pop3_message_t r7;
assert(parse_pop3_message("DELE 724\n", &r7) == true);
assert(r7.message_type == DELETE);
assert(r7.username == NULL);
assert(r7.password == NULL);
assert(r7.target_email == 724);

pop3_message_t r8;
assert(parse_pop3_message("POTATO\n", &r8) == false);

pop3_message_t r9;
assert(parse_pop3_message("APOP user\n", &r9) == false);

pop3_message_t r10;
assert(parse_pop3_message("QUIT 10\n", &r10) == false);





