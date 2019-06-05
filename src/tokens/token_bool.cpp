#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token
{
    TokenBool::TokenBool(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    Type TokenBool::getType() {
        return Type::Bool;
    }
} // JsonStreamAnalyzer::Token
