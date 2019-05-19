#ifndef TOKEN_BRACES_OPEN_INCLUDED
#define TOKEN_BRACES_OPEN_INCLUDED

#include <json-stream-analyzer/token.h>
#include <json-stream-analyzer/io_buffer.h>

namespace JsonStreamAnalyzer::Token {
    class TokenBracesOpen : public Token {
    public:
        TokenBracesOpen(int line, int column, IOReader *reader);

        int getType();
    };
}

#endif