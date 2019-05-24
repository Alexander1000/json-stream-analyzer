#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer::Token
{
    TokenComma::TokenComma(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader) : Token(line, column, reader) {
    }

    int TokenComma::getType() {
        return TOKEN_TYPE_COMMA;
    }
} // JsonStreamAnalyzer::Token
