#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct _ppp_frame {
    uint16_t ppp_protocol_id;
    uint16_t information_len;
    uint8_t* information;
    uint16_t checksum;
} ppp_frame_t;

// Parse a PPP frame from the given binary data into the
// supplied structure. PPP is big endian. 
// PPP packets begin with an 8-bit flag that must be 0x7E
// followed by an 8-bit standard broadcast address that must be 0xFF
// followed by an 8-bit control byte that must be 0x03
// followed by a 16-bit PPP protocol id
// all remaining bytes except the last 3 are the information payload
// finally the last 3 bytes are a 16-bit checksum followed by a 8-bit byte that must be 0x7E
// The information array should be allocated on the heap and will be freed by the caller.
// Do not validate the checksum.
// Return true on a successful parse and false on a failure.

bool parse_ppp_frame(uint8_t* data, int data_len, ppp_frame_t* frame) { //***

}
//***
ppp_frame_t r0;
uint8_t data0[] = {0x7E,
                   0xFF,
                   0x03,
                   0x00, 0x21,
                   0x00, 0x01, 0x00, 0x01,
                   0x00, 0x02,
                   0x7E};
assert(parse_ppp_frame(data0, 12, &r0) == true);
assert(r0.ppp_protocol_id == 33);
assert(r0.information_len == 4);
assert(memcmp(r0.information, data0+5, 4) == 0);
assert(r0.checksum == 2);
free(r0.information);

ppp_frame_t r1;
uint8_t data1[] = {0x7F,
                   0xFF,
                   0x03,
                   0x00, 0x21,
                   0x00, 0x01, 0x00, 0x01,
                   0x00, 0x02,
                   0x7E};
assert(parse_ppp_frame(data1, 12, &r1) == false);

ppp_frame_t r2;
uint8_t data2[] = {0x7E,
                   0xFF,
                   0x04,
                   0x00, 0x21,
                   0x00, 0x01, 0x00, 0x01,
                   0x00, 0x02,
                   0x7E};
assert(parse_ppp_frame(data2, 12, &r2) == false);

ppp_frame_t r3;
uint8_t data3[] = {0x7E,
                   0xFE,
                   0x03,
                   0x00, 0x21,
                   0x00, 0x01, 0x00, 0x01,
                   0x00, 0x02,
                   0x7E};
assert(parse_ppp_frame(data3, 12, &r3) == false);

ppp_frame_t r4;
uint8_t data4[] = {0x7E,
                   0xFF,
                   0x03,
                   0x00, 0x21,
                   0x00, 0x02};
assert(parse_ppp_frame(data4, 7, &r4) == false);