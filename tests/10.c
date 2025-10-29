#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    REQUEST = 1,
    REPLY = 2
} arp_operation_t;

typedef struct _arp_ipv4_ethernet_packet {
    arp_operation_t operation;
    uint8_t sender_hardware_address[6];
    uint32_t sender_protocol_address;
    uint8_t target_hardware_address[6];
    uint32_t target_protocol_address;
} arp_ipv4_ethernet_packet_t;

// Parse a ARP IPv4 request/reply packet over ethernet from the given binary data into the
// supplied structure. Only fill the fields that are in the structure, but ensure all 
// fields are valid for ARP over Ethernet for IPv4.
// The header is big endian
// It is arranged as a 16-bit hardware type (must be 1 for ethernet), 
// then a 16-bit protocol type (must be 0x0800 for IPv4)
// then an 8-bit hardware address length in octets (must be 6 for ethernet)
// then an 8-bit internetwork address length in octets (must be 4 for IPv4)
// then a 16-bit operation (1=request, 2=recieve)
// then the sender hardware address (6 bytes for ethernet)
// then the sender internetwork address (4 bytes for ethernet)
// then the target hardware address (6 bytes for ethernet)
// then the target internetwork address (4 bytes for ethernet)
// Return true on a successful parse and false on a failure.

bool parse_arp_ipv4_ethernet_packet(uint8_t* data, int data_len, arp_ipv4_ethernet_packet_t* packet) { //***

}
//***
arp_ipv4_ethernet_packet_t r0;
uint8_t data0[] = {0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01,
                   0x50, 0xAA, 0x00, 0x06, 0x00, 0x07, 
                   0x00, 0x08, 0x00, 0x08,
                   0x51, 0xA1, 0x01, 0x01, 0x01, 0x01, 
                   0x01, 0x01, 0x01, 0x01};
assert(parse_arp_ipv4_ethernet_packet(data0, 28, &r0) == true);
assert(r0.operation == REQUEST);
assert(memcmp(r0.sender_hardware_address, data0+8, 6) == 0);
assert(r0.sender_protocol_address == 0x00080008);
assert(memcmp(r0.target_hardware_address, data0+18, 6) == 0);
assert(r0.target_protocol_address == 0x01010101);

arp_ipv4_ethernet_packet_t r1;
uint8_t data1[] = {0x00, 0x04, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01,
                   0x50, 0xAA, 0x00, 0x06, 0x00, 0x07, 
                   0x00, 0x08, 0x00, 0x08,
                   0x51, 0xA1, 0x01, 0x01, 0x01, 0x01, 
                   0x01, 0x01, 0x01, 0x01};
assert(parse_arp_ipv4_ethernet_packet(data1, 28, &r1) == false);

arp_ipv4_ethernet_packet_t r2;
uint8_t data2[] = {0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01,
                   0x50, 0xAA, 0x00, 0x06, 0x00, 0x07, 
                   0x00, 0x08, 0x00, 0x08,
                   0x51, 0xA1, 0x01, 0x01, 0x01, 0x01, 
                   0x01, 0x01, 0x01};
assert(parse_arp_ipv4_ethernet_packet(data2, 27, &r2) == false);

arp_ipv4_ethernet_packet_t r3;
uint8_t data3[] = {0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x03,
                   0x50, 0xAA, 0x00, 0x06, 0x00, 0x07, 
                   0x00, 0x08, 0x00, 0x08,
                   0x51, 0xA1, 0x01, 0x01, 0x01, 0x01, 
                   0x01, 0x01, 0x01, 0x03};
assert(parse_arp_ipv4_ethernet_packet(data3, 28, &r3) == false);
