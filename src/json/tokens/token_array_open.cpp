#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer::Token {
    TokenArrayOpen::TokenArrayOpen(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader) : Token(line, column, reader) {
    }

    int TokenArrayOpen::getType() {
        return TOKEN_TYPE_ARRAY_OPEN;
    }
} // JsonStreamAnalyzer::Token
