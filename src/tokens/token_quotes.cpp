#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token
{
    TokenQuotes::TokenQuotes(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    int TokenQuotes::getType() {
        return TOKEN_TYPE_QUOTES;
    }
} // JsonStreamAnalyzer::Token
