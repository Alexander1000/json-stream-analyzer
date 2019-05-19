#ifndef TOKEN_ARRAY_CLOSE_INCLUDED
#define TOKEN_ARRAY_CLOSE_INCLUDED

#include <json-stream-analyzer/token.h>
#include <json-stream-analyzer/io_buffer.h>

namespace JsonStreamAnalyzer::Token {
    class TokenArrayClose : public Token {
    public:
        TokenArrayClose(int line, int column, IOReader *reader);
        int getType();
    };
}

#endif