#define STREAM_BUFFER_SIZE 4096

#define JSON_LEXER_PLAIN_MODE 0
#define JSON_LEXER_TEXT_MODE 1
#define JSON_LEXER_DIGIT_MODE 2
#define JSON_LEXER_WORD_MODE  3

#include "tokens/token.h"

#include "stream.cpp"
#include "pretty.cpp"

#include "object/object.h"
#include "decoder.cpp"
