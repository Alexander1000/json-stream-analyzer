#include "stream.cpp"
#include "pretty.cpp"

#define STREAM_BUFFER_SIZE = 4096;

#define PLAIN_MODE 0
#define TEXT_MODE 1
#define VALUE_MODE 2
#define OBJECT_ATTRIBUTE_MODE 3
#define SCAN_COMMA_MODE 4
#define OBJECT_ATTRIBUTE_VALUE_MODE 5
#define SCAN_SEPARATOR_MODE 4

#define JSON_LEXER_PLAIN_MODE 0
#define JSON_LEXER_TEXT_MODE 1