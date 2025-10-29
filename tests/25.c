#include <stdlib.h>
#include <string.h>

#define SSL3_VERSION                    0x0300
#define TLS1_VERSION                    0x0301
#define TLS1_1_VERSION                  0x0302
#define TLS1_2_VERSION                  0x0303
#define TLS1_3_VERSION                  0x0304
#define DTLS1_VERSION                   0xFEFF
#define DTLS1_2_VERSION                 0xFEFD

// Extract the integer protocol identifier defined above based on a string.
// The following strings are valid inputs:
//    "None", "SSLv3", "TLSv1", "TLSv1.1", 
//    "TLSv1.2", "TLSv1.3", "DTLSv1", "DTLSv1.2"
// The function should return -1 on invalid strings, and 0 for None

int protocol_from_string(const char *value) { //***
    struct protocol_versions {
        const char *name;
        int version;
    };
    /*
     * Note: To avoid breaking previously valid configurations, we must retain
     * legacy entries in this table even if the underlying protocol is no
     * longer supported.  This also means that the constants SSL3_VERSION, ...
     * need to be retained indefinitely.  This table can only grow, never
     * shrink.
     */
    static const struct protocol_versions versions[] = {
        {"None", 0},
        {"SSLv3", SSL3_VERSION},
        {"TLSv1", TLS1_VERSION},
        {"TLSv1.1", TLS1_1_VERSION},
        {"TLSv1.2", TLS1_2_VERSION},
        {"TLSv1.3", TLS1_3_VERSION},
        {"DTLSv1", DTLS1_VERSION},
        {"DTLSv1.2", DTLS1_2_VERSION}
    };
    size_t i;
    size_t n = sizeof(versions)/(sizeof(versions[0]));

    for (i = 0; i < n; i++)
        if (strcmp(versions[i].name, value) == 0)
            return versions[i].version;
    return -1;
}
// HUMAN NOTE: From OpenSSL ssl/ssl_conf.c - changes made
//***
assert(protocol_from_string("None") == 0);
assert(protocol_from_string("SSLv3") == SSL3_VERSION);
assert(protocol_from_string("TLSv1") == TLS1_VERSION);
assert(protocol_from_string("TLSv1.1") == TLS1_1_VERSION);
assert(protocol_from_string("TLSv1.2") == TLS1_2_VERSION);
assert(protocol_from_string("TLSv1.3") == TLS1_3_VERSION);
assert(protocol_from_string("DTLSv1.2") == DTLS1_2_VERSION);
assert(protocol_from_string("DTLSv1") == DTLS1_VERSION);
assert(protocol_from_string("potato") == -1);
assert(protocol_from_string("") == -1);


