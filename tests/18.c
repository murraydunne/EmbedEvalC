#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    TCPIP_STREAM = 1,
    TCPIP_BINDING = 2
} socks_command_code_t;

typedef struct _socks_request {
    socks_command_code_t command;
    uint16_t destination_port;
    uint32_t destination_ipv4_address;
    char* user_id;
} socks_request_t;

// Parse a SOCKS request frame from the given binary data into the
// supplied structure. SOCKS is big endian. 
// SOCKS requests begin with an 8-bit version number, which must be 4.
// This is followed by an 8-bit command code (stream=1, binding=2).
// Then there is a 16-bit destination port and 32-bit destination IPv4 address.
// Finally there is a null-termianted string that is the user id.
// The user id string should be allocated on the heap and will be freed by the caller.
// Return true on a successful parse and false on a failure.

bool parse_socks_request(uint8_t* data, int data_len, socks_request_t* request) { //***

}
//***
socks_request_t r0;
uint8_t data0[] = {0x04,
                   0x02,
                   0x01, 0x02,
                   0xAA, 0xBB, 0xCC, 0xDD,
                   0x48, 0x49, 0x00};
assert(parse_socks_request(data0, 11, &r0) == true);
assert(r0.command == TCPIP_BINDING);
assert(r0.destination_port == 258);
assert(r0.destination_ipv4_address == 0xAABBCCDD);
assert(strcmp(r0.user_id, "HI") == 0);
free(r0.user_id);

socks_request_t r1;
uint8_t data1[] = {0x04,
                   0x02,
                   0x01, 0x02,
                   0xAA, 0xBB, 0xCC};
assert(parse_socks_request(data1, 7, &r1) == false);


socks_request_t r2;
uint8_t data2[] = {0x05,
                   0x02,
                   0x01, 0x02,
                   0xAA, 0xBB, 0xCC, 0xDD,
                   0x48, 0x49, 0x00};
assert(parse_socks_request(data2, 11, &r2) == false);

