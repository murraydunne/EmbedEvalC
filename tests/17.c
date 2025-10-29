#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>


typedef struct _modbus_pdu {
    uint8_t function_code;
    uint16_t data;
} modbus_pdu_t;

// Parse an MODBUS PDU from the given binary data into the supplied structure.
// A MODBUS PDU is encoded in big endian.
// A MODBUS PDU begins with an 8-bit function follwed by a 16-bit data field.
// Return true on a successful parse and false on a failure.

bool parse_modbus_pdu(uint8_t* data, int data_len_bytes, modbus_pdu_t* frame) { //***

}
//***
modbus_pdu_t r0;
uint8_t data0[] = {0xAA, 0x01, 0x01};
assert(parse_modbus_pdu(data0, 3, &r0) == true);
assert(r0.function_code == 170);
assert(r0.data == 257);

modbus_pdu_t r1;
uint8_t data1[] = {0xAA, 0x01};
assert(parse_modbus_pdu(data1, 2, &r1) == false);