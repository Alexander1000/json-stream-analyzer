#ifndef JSON_STREAM_INCLUDED
#define JSON_STREAM_INCLUDED

#define STREAM_BUFFER_SIZE 4096

#define JSON_LEXER_PLAIN_MODE 0
#define JSON_LEXER_TEXT_MODE 1
#define JSON_LEXER_DIGIT_MODE 2
#define JSON_LEXER_WORD_MODE  3

#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer {
    class Stream {
    public:
        Stream(IOReader *reader);
        Token::Token *get_next_token();
    };
}

#endif /* JSON_STREAM_INCLUDED */
