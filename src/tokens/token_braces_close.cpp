#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token
{
    TokenBracesClose::TokenBracesClose(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    int TokenBracesClose::getType() {
        return TOKEN_TYPE_BRACES_CLOSE;
    }
} // JsonStreamAnalyzer::Token
