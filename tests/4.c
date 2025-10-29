#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct _ip_address {
    bool is_ipv6;
    union {
        struct {
            uint16_t routing2;
            uint16_t routing1;
            uint16_t routing0;
            uint16_t subnet_prefix;
            uint16_t local3;
            uint16_t local2;
            uint16_t local1;
            uint16_t local0;
        } ipv6;
        struct {
            uint8_t octet3;
            uint8_t octet2;
            uint8_t octet1;
            uint8_t octet0;
        } ipv4;
    };
} ip_address_t;

// Parse an IP Address from a string into the provided structure.
// The address could be IPv4 or IPv6.
// An IPv4 address is given as 4 octets separated by .
// For example 127.0.0.1 would become 127,0,0,1 as octets 3,2,1,0
// An IPv6 address is given as hexadecimal 16-bit integers separated by :
// Leading zeros can be omitted from the hexadecimal integers, but one digit must remain.
// Excepting that the longest leftmost sequence of zeros may be replaced by :: instead
// For example 20:0:AA::0101 would become 32,0,170,0,0,0,0,257 as routing 2,1,0 then subnet, then local 3,2,1,0
// Return true if the parse was successful, and false otherwise

bool parse_ip_address(const char* string_ip, ip_address_t* address) { //***

}
//***
ip_address_t r0;
assert(parse_ip_address("192.168.1.1", &r0) == true);
assert(r0.is_ipv6 == false);
assert(r0.ipv4.octet0 == 1);
assert(r0.ipv4.octet1 == 1);
assert(r0.ipv4.octet2 == 168);
assert(r0.ipv4.octet3 == 192);

ip_address_t r1;
assert(parse_ip_address("AA40::0010", &r1) == true);
assert(r1.is_ipv6 == true);
assert(r1.ipv6.routing2 == 0xAA40);
assert(r1.ipv6.routing1 == 0);
assert(r1.ipv6.routing0 == 0);
assert(r1.ipv6.subnet_prefix == 0);
assert(r1.ipv6.local3 == 0);
assert(r1.ipv6.local2 == 0);
assert(r1.ipv6.local1 == 0);
assert(r1.ipv6.local0 == 0x0010);

ip_address_t r2;
assert(parse_ip_address("1234:567:022::2:1", &r2) == true);
assert(r2.is_ipv6 == true);
assert(r2.ipv6.routing2 == 0x1234);
assert(r2.ipv6.routing1 == 0x567);
assert(r2.ipv6.routing0 == 0x22);
assert(r2.ipv6.subnet_prefix == 0);
assert(r2.ipv6.local3 == 0);
assert(r2.ipv6.local2 == 0);
assert(r2.ipv6.local1 == 2);
assert(r2.ipv6.local0 == 1);

ip_address_t r3;
assert(parse_ip_address("124.567.022.2.1", &r3) == false);

ip_address_t r4;
assert(parse_ip_address("1234.567", &r4) == false);

ip_address_t r5;
assert(parse_ip_address("1234A::567", &r5) == false);