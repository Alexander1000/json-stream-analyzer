#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token
{
    TokenArrayClose::TokenArrayClose(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    Type TokenArrayClose::getType() {
        return Type::ArrayClose;
    }
} // JsonStreamAnalyzer::Token
