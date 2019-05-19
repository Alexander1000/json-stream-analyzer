#ifndef TOKEN_COLON_INCLUDED
#define TOKEN_COLON_INCLUDED

#include <json-stream-analyzer/token.h>
#include <json-stream-analyzer/io_buffer.h>

namespace JsonStreamAnalyzer::Token {
    class TokenColon : public Token {
    public:
        TokenColon(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader);

        int getType();
    };
}

#endif
