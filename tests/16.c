#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>

typedef struct _xml_node {
    char* tag;
    char* content;
    int num_children;
    struct _xml_node* children;
} xml_node_t;

// Parse a XML tree from a string into the specified structure.
// XML tags may have children, or content, but not both.
// If a tag does not have children or does not have content, that field should be NULL;
// And XML tag begins with a < character, then has a tag name
// that can be alphanumeric but must start with a letter, then a > character
// A tag can be self-closing in which case it ends with a /> instead and
// has neither content nor children.
// If a tag is not self-closing it can contain either an text (except a <)
// or more XML tags which should be placed in the children array in order.
// XML tags after the root tag should be allocated on the heap and will be freed
// by the caller.
// The content and tag strings should be allocated on the heap and will be freed
// by the caller.
// Only parse XML tags with no attributes. A tag with an attribute should fail to parse.
// Return true on a successful parse and false on a failure.

bool parse_xml(const char* xml_string, xml_node_t* root) { //***

}
//***
xml_node_t r0;
assert(parse_xml("<root><c1/><c2>test</c2></root>", &r0) == true);
assert(r0.num_children == 2);
assert(strcmp(r0.tag, "root") == 0);
assert(strcmp(r0.children[0].tag, "c1") == 0);
assert(r0.children[0].content == NULL);
assert(r0.children[0].children == NULL);
assert(r0.children[0].num_children == 0);
assert(strcmp(r0.children[1].tag, "c2") == 0);
assert(strcmp(r0.children[1].content, "test") == 0);
assert(r0.children[1].children == NULL);
assert(r0.children[1].num_children == 0);
free(r0.children[0].tag);
free(r0.children[1].tag);
free(r0.children[1].content);
free(r0.children);