#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>


typedef struct _can_frame {
    uint32_t identifier;
    bool is_request_frame;
    uint8_t data_length;
    uint8_t data[8];
    uint16_t crc;
} can_frame_t;

// Parse an CAB frame from the given binary data into the
// supplied structure. CAN sends bits in big-endian order across the entire intger.
// Assume the input has no stuffing bits (they have already been removed).
// Only fill the fields that are in the structure.
// A CAN packet begins with 1 start of frame bit, then 11 identifier bits,
// then 1 substitute remote request bit (this is the request bit for 11-bit identifier frames),
// then 1 identifier extension bit and extended identifier 
// (if this bit is 1 then the next 18 bits are the next 18 bits of the identifier, 
// making it an extended identifier, if it 0 then there are no more identifier bits
// and the substitute remote request bit is actually the request bit),
// then if it's an extended identifier there is the remote request bit,
// then for both identifier types there are 2 reserved bit, 
// and then a 4-bit data-length, followed by
// data-length number of data bytes, followed by a 16-bit CRC (last bit always 1).
// Do not validate the CRC.
// There may be spare bits on the end of a message, they can be ignored.
// Return true on a successful parse and false on a failure.

bool parse_can_packet(uint8_t* data, int data_len_bytes, can_frame_t* frame) { //***

}
//***

can_frame_t r0;
// 1 00000000000 11 000000000000000001 1 00 0010 00000001 00000010 0000000000001111
// 10000000 00001100 00000000 00000001 10000100 00000010 00000100 00000000 0001111_0
uint8_t data0[] = {0x80, 0x0C, 0x00, 0x01, 0x84, 0x02, 0x04, 0x00, 0x1E};
assert(parse_can_packet(data0, 9, &r0) == true);
assert(r0.identifier == 1);
assert(r0.is_request_frame == true);
assert(r0.data_length == 2);
assert(r0.data[0] == 1);
assert(r0.data[1] == 2);
assert(r0.crc == 0x000F);

can_frame_t r1;
// 1 00000000011 00 00 0010 00000001 00000010 0000000000001111
// 10000000 00110000 00100000 00010000 00100000 00000000 1111
uint8_t data1[] = {0x80, 0x30, 0x20, 0x10, 0x20, 0x00, 0xF0};
assert(parse_can_packet(data1, 7, &r1) == true);
assert(r1.identifier == 3);
assert(r1.is_request_frame == false);
assert(r1.data_length == 2);
assert(r1.data[0] == 1);
assert(r1.data[1] == 2);
assert(r1.crc == 0x000F);

can_frame_t r2;
// 1 00000000011 00 00 0010 00000001 00000010 0000000000001111
// 10000000 00110000 00100000 00010000 00100000 00000000 1111
uint8_t data2[] = {0x80, 0x30, 0x20};
assert(parse_can_packet(data1, 3, &r2) == false);

can_frame_t r3;
// 1 00000000011 00 00 0010 00000001 00000010 0000000000001111
// 10000000 00110000 00100000 00010000 00100000 00000000 1111
uint8_t data3[] = {0x80, 0x30, 0x20, 0x10, 0x20};
assert(parse_can_packet(data1, 5, &r3) == false);
