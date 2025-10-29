#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>


typedef struct _mavlink_v2_message {
    uint8_t payload_len;
    uint8_t incompatibility_flags;
    uint8_t compatibilty_flags;
    uint8_t sequence_number;
    uint8_t sender_sys_id;
    uint8_t sender_component_id;
    uint32_t message_id;
    uint8_t* payload;
    uint16_t checksum;
    uint8_t signature[13];
} mavlink_v2_message_t;

// Parse a Mavlink v2 message from the given binary data into the
// supplied structure. Only fill the fields that are in the structure.
// Mavlink message are arranged as an 8-bit magic id that must be 0xFD
// followed by an 8-bit payload length, then an 8-bit incompatibility flags,
// then an 8-bit compatibilty flags, then an 8-bit sequence number, then
// an 8-bit sender system id, then an 8-bit sender component id, then
// an 24-bit message id in little-endian byte order, then the patload of
// length bytes as specified earlier, then a 16-bit checksum in little-endian,
// and finally an optional 13-byte signature.
// The payload array should be allocated on the heap and will be freed by the caller.
// Do not validate the checksum. Do not validate the signature.
// Return true on a successful parse and false on a failure.

bool parse_mavlink_v2_message(uint8_t* data, int data_len, mavlink_v2_message_t* message) { //***

}
//***
mavlink_v2_message_t r0;
uint8_t data0[] = {0xFD,
                   0x02,
                   0x00,
                   0x00,
                   0x0F,
                   0x10,
                   0x20,
                   0xAA, 0xBB, 0xCC,
                   0x12, 0x34,
                   0x00, 0x01,
                   0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D};
assert(parse_mavlink_v2_message(data0, 27, &r0) == true);
assert(r0.payload_len == 2);
assert(r0.incompatibility_flags == 0);
assert(r0.compatibilty_flags == 0);
assert(r0.sequence_number == 15);
assert(r0.sender_sys_id == 16);
assert(r0.sender_component_id == 32);
assert(r0.message_id == 0xCCBBAA);
assert(memcmp(r0.payload, data0+10, 2) == 0);
assert(r0.checksum == 256);
assert(memcmp(r0.signature, data0+14, 13) == 0);
free(r0.payload);

mavlink_v2_message_t r1;
uint8_t data1[] = {0xFD,
                   0x02,
                   0x00,
                   0x00,
                   0x0F,
                   0x10,
                   0x20,
                   0xAA, 0xBB, 0xCC,
                   0x12, 0x34,
                   0x00, 0x01};
assert(parse_mavlink_v2_message(data1, 14, &r1) == true);
assert(r1.payload_len == 2);
assert(r1.incompatibility_flags == 0);
assert(r1.compatibilty_flags == 0);
assert(r1.sequence_number == 15);
assert(r1.sender_sys_id == 16);
assert(r1.sender_component_id == 32);
assert(r1.message_id == 0xCCBBAA);
assert(memcmp(r1.payload, data0+10, 2) == 0);
assert(r1.checksum == 256);
free(r1.payload);

mavlink_v2_message_t r2;
uint8_t data2[] = {0xFE,
                   0x02,
                   0x00,
                   0x00,
                   0x0F,
                   0x10,
                   0x20,
                   0xAA, 0xBB, 0xCC,
                   0x12, 0x34,
                   0x00, 0x01};
assert(parse_mavlink_v2_message(data2, 14, &r2) == false);

mavlink_v2_message_t r3;
uint8_t data3[] = {0xFD,
                   0x04,
                   0x00,
                   0x00,
                   0x0F,
                   0x10,
                   0x20,
                   0xAA, 0xBB, 0xCC,
                   0x12, 0x34,
                   0x00, 0x01};
assert(parse_mavlink_v2_message(data3, 14, &r3) == false);