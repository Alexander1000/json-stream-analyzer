#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer::Token
{
    TokenColon::TokenColon(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader) : Token(line, column, reader) {
    }

    int TokenColon::getType() {
        return TOKEN_TYPE_COLON;
    }
} // JsonStreamAnalyzer::Token
