#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token
{
    TokenColon::TokenColon(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    int TokenColon::getType() {
        return TOKEN_TYPE_COLON;
    }
} // JsonStreamAnalyzer::Token
