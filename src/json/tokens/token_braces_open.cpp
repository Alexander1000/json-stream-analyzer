#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer::Token
{
    TokenBracesOpen::TokenBracesOpen(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader) : Token(line, column, reader) {
    }

    int TokenBracesOpen::getType() {
        return TOKEN_TYPE_BRACES_OPEN;
    }
} // JsonStreamAnalyzer::Token
