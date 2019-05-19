#ifndef TOKEN_ARRAY_OPEN_INCLUDED
#define TOKEN_ARRAY_OPEN_INCLUDED

#include <json-stream-analyzer/token.h>
#include <json-stream-analyzer/io_buffer.h>

namespace JsonStreamAnalyzer::Token {
    class TokenArrayOpen : public Token {
    public:
        TokenArrayOpen(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader);

        int getType();
    };
}

#endif