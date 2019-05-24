#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer::Token
{
    TokenBracesClose::TokenBracesClose(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader) : Token(line, column, reader) {
    }

    int TokenBracesClose::getType() {
        return TOKEN_TYPE_BRACES_CLOSE;
    }
} // JsonStreamAnalyzer::Token
