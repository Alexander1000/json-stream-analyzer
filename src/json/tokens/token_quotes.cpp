#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer::Token
{
    TokenQuotes::TokenQuotes(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader) : Token(line, column, reader) {
    }

    int TokenQuotes::getType() {
        return TOKEN_TYPE_QUOTES;
    }
} // JsonStreamAnalyzer::Token
