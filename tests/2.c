#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    QUERY = 0,
    IQUERY = 1,
    STATUS = 2
} dns_opcode_t;

typedef struct _dns_header {
    uint16_t transaction_id;
    bool is_query;
    dns_opcode_t opcode;
    bool is_authoriative;
    bool is_trucated;
    bool wants_recursion;
    bool is_recursion_available;
    uint8_t response_code;
    uint16_t num_questions;
    uint16_t num_answers;
    uint16_t num_authority_rrs;
    uint16_t num_additional_rrs;
} dns_header_t;

// Parse a DNS request header from the given binary data into the 
// supplied structure.
// The DNS header is big endian for 16-bits.
// It is arranged as a 16-bit transaction id,
// then 1 bit of query (0=query, 1=response), 4 bits opcode (as the enum), 
// 1 bit authoriative, 1 bit truncated
// 1 bit recursion request, 1 bit has recursion, 3 forced zero bits (must be zero), and 4 response code bits
// then 4x 16-bits each for num questions, answer, authority RRs, and additional RRs
// Return true on a successful parse and false on a failure.

bool parse_dns_header(uint8_t* data, int data_len, dns_header_t* dns) { //***

}
//***
dns_header_t r0;
uint8_t data0[] = {0x00, 0x01, 0x87, 0x8F, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04, 0x00, 0x05};
assert(parse_dns_header(data0, 12, &r0) == true);
assert(r0.transaction_id == 1);
assert(r0.is_query == false);
assert(r0.opcode == QUERY);
assert(r0.is_authoriative == true);
assert(r0.is_trucated == true);
assert(r0.wants_recursion == true);
assert(r0.is_recursion_available == true);
assert(r0.response_code == 15);
assert(r0.num_questions == 2);
assert(r0.num_answers == 3);
assert(r0.num_authority_rrs == 4);
assert(r0.num_additional_rrs == 5);

dns_header_t r1;
uint8_t data1[] = {0x00, 0x01, 0xE0, 0xFF, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04, 0x00, 0x05};
assert(parse_dns_header(data1, 12, &r1) == false);

dns_header_t r2;
uint8_t data2[] = {0x00, 0x01};
assert(parse_dns_header(data2, 2, &r2) == false);