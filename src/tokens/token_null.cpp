#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token
{
    TokenNull::TokenNull(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    Type TokenNull::getType() {
        return Type::Null;
    }
} // JsonStreamAnalyzer::Token
