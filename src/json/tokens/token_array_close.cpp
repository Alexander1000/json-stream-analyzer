#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer::Token
{
    TokenArrayClose::TokenArrayClose(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader) : Token(line, column, reader) {
    }

    int TokenArrayClose::getType() {
        return TOKEN_TYPE_ARRAY_CLOSE;
    }
} // JsonStreamAnalyzer::Token
