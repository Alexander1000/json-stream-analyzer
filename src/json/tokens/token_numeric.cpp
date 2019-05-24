#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer::Token
{
    TokenNumeric::TokenNumeric(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader) : Token(line, column, reader) {
    }

    int TokenNumeric::getType() {
        return TOKEN_TYPE_NUMERIC;
    }
} // JsonStreamAnalyzer::Token
