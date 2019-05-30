#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token
{
    TokenBracesClose::TokenBracesClose(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    Type TokenBracesClose::getType() {
        return Type::BracesClose;
    }
} // JsonStreamAnalyzer::Token
