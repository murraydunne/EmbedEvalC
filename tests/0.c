#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    GET,
    POST,
    PUT,
    DELETE
} http_method_t;

typedef enum {
    NONE = 0,
    GZIP = 1,
    DEFLATE = 2
} encoding_flags_t;

typedef struct _http_request {
    http_method_t method;
    encoding_flags_t encodings;
    char* filename;
    bool keep_alive;
    int content_length;
    uint8_t* content;
} http_request_t;

// Parse and HTTP/1.1 (only 1.1 accepted) request from a string into the supplied request structure
// Extract all the fields to fill the provided http_request structure.
// HTTP/1.1 requests being with a method and filename declaration
// followed by request parameters separated by \r\n
// A sequence of \r\n\r\n marks the beginning of the content.
// Return true after a successful parse, false otherwise.
// If a field is missing, set it to zero or NULL as appropriate.
// - method should be the HTTP method of the request
// - encodings should be all the encodings listed by Accept-Encoding:
// - filename should be the absolute file path requested
//      - string allocated on the heap and freed by caller if the parse was a success
// - keep alive should be true if Connection: keep-alive is specified
// - content_length is the length of supplied content (mostly for PUT and POST)
// - content is the binary content of the message
//      - binary block allocated on the heap and freed by caller if the parse was a success

bool parse_http_request(const char* request, http_request_t* fill) { //***

} //***
// unfair for now?
/// parse_http_request("GET index.html HTTP/1.1\r\n\r\n", &request) -> request.filname == "index.html"
http_request_t r1;
assert(parse_http_request("GET favicon.ico HTTP/1.1\r\n\r\n", &r1) == true);
assert(strcmp(r1.filename, "favicon.ico") == 0);
assert(r1.method == GET);
assert(r1.keep_alive == false);
assert(r1.encodings == 0);
assert(r1.content_length == 0);
assert(r1.content == NULL);
free(r1.filename);

http_request_t r2;
assert(parse_http_request("POST /users/text/story.txt HTTP/1.1\r\n" 
    "Accept-Encoding: gzip,deflate\r\n"
    "Content-Length: 12\r\n"
    "Connection: keep-alive\r\n"
    "\r\n"
    "I love dogs!", &r2) == true);
assert(strcmp(r2.filename, "/users/text/story.txt") == 0);
assert(r2.method == POST);
assert(r2.keep_alive == true);
assert(r2.encodings == GZIP|DEFLATE);
assert(r2.content_length == 12);
assert(memcmp(r2.content, "I love dogs!", 12) == 0);
free(r2.filename);
free(r2.content);

http_request_t r3;
assert(parse_http_request("PUT /users/text/story.txt HTTP/1.0\r\n\r\n", &r3) == false);

http_request_t r4;
assert(parse_http_request("DELETE /users/text/story.txt HTTP/1.1\r\n" 
    "Content-Length: 0\r\n"
    "Accept-Encoding: gzip\r\n"
    "\r\n", &r4) == true);
assert(strcmp(r4.filename, "/users/text/story.txt") == 0);
assert(r4.method == DELETE);
assert(r4.keep_alive == false);
assert(r4.encodings == GZIP);
assert(r4.content_length == 0);
assert(r4.content == NULL);
free(r4.filename);


