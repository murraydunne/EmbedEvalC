#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct _udp_packet {
    uint16_t source_port;
    uint16_t dest_port;
    uint16_t length;
    uint16_t checksum;
    uint8_t* data;
} udp_packet_t;

// Parse a UDP packet from the given binary data into the
// supplied structure.
// The UDP header is big endian
// It is arranged as a 16-bit source port, 16 bit destination port
// 16-bit length (including the 8 bytes of header), then a 16-bit checksum,
// then the data.
// Do not validate the checksum.
// Copy the data into a new byte array allocated on the heap. It will be freed by the caller.
// Return true on a successful parse and false on a failure.

bool parse_udp_packet(uint8_t* data, int data_len, udp_packet_t* packet) { //***

}
//***
udp_packet_t r0;
uint8_t data0[] = {0x00, 0x01, 0x00, 0x02, 0x00, 0x12, 0x00, 0x01,
                   0x50, 0xAA, 0x00, 0x06, 0x00, 0x07, 0x00, 0x08, 0x00, 0x08};
assert(parse_udp_packet(data0, 18, &r0) == true);
assert(r0.source_port == 1);
assert(r0.dest_port == 2);
assert(r0.length == 18);
assert(r0.checksum == 1);
assert(memcmp(r0.data, data0+8, 10) == 0);
free(r0.data);

udp_packet_t r1;
uint8_t data1[] = {0x00, 0x01, 0x00, 0x02, 0x00, 0x0A, 0x00, 0x01,
                   0x50, 0xAA, 0x00, 0x06, 0x00, 0x07, 0x00, 0x08};
assert(parse_udp_packet(data1, 16, &r1) == false);

