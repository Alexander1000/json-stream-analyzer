#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token
{
    TokenQuotes::TokenQuotes(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    Type TokenQuotes::getType() {
        return Type::Quotes;
    }
} // JsonStreamAnalyzer::Token
