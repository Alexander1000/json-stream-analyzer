#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token
{
    TokenArrayOpen::TokenArrayOpen(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    int TokenArrayOpen::getType() {
        return TOKEN_TYPE_ARRAY_OPEN;
    }
} // JsonStreamAnalyzer::Token
