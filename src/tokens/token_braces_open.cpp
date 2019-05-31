#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token
{
    TokenBracesOpen::TokenBracesOpen(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    Type TokenBracesOpen::getType() {
        return Type::BracesOpen;
    }
} // JsonStreamAnalyzer::Token
