#ifndef TOKEN_COMMA_INCLUDED
#define TOKEN_COMMA_INCLUDED

#include <json-stream-analyzer/token.h>
#include <json-stream-analyzer/io_buffer.h>

namespace JsonStreamAnalyzer::Token {
    class TokenComma : public Token {
    public:
        TokenComma(int line, int column, IOReader *reader);

        int getType();
    };
}

#endif
