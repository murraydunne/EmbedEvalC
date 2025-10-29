#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct _tcp_header {
    uint16_t source_port;
    uint16_t dest_port;
    uint32_t sequence_number;
    uint32_t ack_number;
    uint8_t data_offset;
    bool cwr_flag;
    bool ece_flag;
    bool urg_flag;
    bool ack_flag;
    bool psh_flag;
    bool rst_flag;
    bool syn_flag;
    bool fin_flag;
    uint16_t window_size;
    uint16_t checksum;
    uint16_t urgent;
} tcp_header_t;

// Parse a TCP packet header from the given binary data into the 
// supplied structure.
// The TCP header is big endian.
// It is arranged as a 16-bit source port, 16 bit destination port
// 32-bit sequence number, 32-bit ack number, then 4 bits data offset,
// 4 bits reserved (ignore), then 8x 1-bit flags: cwr, ece, urg, ack, psh, rst, syn, fin,
// then 16-bit window size, 16-bit checksum, and finally a 16-bit urgent pointer
// Return true on a successful parse and false on a failure.

bool parse_tcp_header(uint8_t* data, int data_len, tcp_header_t* header) { //***

}
//***
tcp_header_t r0;
uint8_t data0[] = {0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04,
                   0x50, 0xAA, 0x00, 0x06, 0x00, 0x07, 0x00, 0x08};
assert(parse_tcp_header(data0, 20, &r0) == true);
assert(r0.source_port == 1);
assert(r0.dest_port == 2);
assert(r0.sequence_number == 3);
assert(r0.ack_number == 4);
assert(r0.data_offset == 5);
assert(r0.cwr_flag == true);
assert(r0.ece_flag == false);
assert(r0.urg_flag == true);
assert(r0.ack_flag == false);
assert(r0.psh_flag == true);
assert(r0.rst_flag == false);
assert(r0.syn_flag == true);
assert(r0.fin_flag == false);
assert(r0.window_size == 6);
assert(r0.checksum == 7);
assert(r0.urgent == 8);

tcp_header_t r1;
uint8_t data1[] = {0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04};
assert(parse_tcp_header(data0, 12, &r0) == false);

