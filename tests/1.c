#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct _icmp_packet {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint32_t rest_of_header;
} icmp_packet_t;

// Parse an ICMP packet from the given binary data into the
// supplied structure.
// The ICMP header is big endian
// It is arranged as a 8-bit type, an 8-bit code, a 16-bit checksum, and the rest is a 32-bit value
// Do not validate the checksum.
// Return true on a successful parse and false on a failure.

bool parse_icmp_packet(uint8_t* data, int data_len, icmp_packet_t* packet) { //***

}
//***
icmp_packet_t r0;
uint8_t data0[] = {0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01};
assert(parse_icmp_packet(data0, 8, &r0) == true);
assert(r0.type == 0);
assert(r0.code == 1);
assert(r0.checksum == 2);
assert(r0.rest_of_header == 1);

icmp_packet_t r1;
uint8_t data1[] = {0x00, 0x01, 0x00, 0x02, 0x00};
assert(parse_icmp_packet(data1, 5, &r1) == false);

