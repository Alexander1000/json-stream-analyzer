#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token
{
    TokenNumeric::TokenNumeric(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    Type TokenNumeric::getType() {
        return Type::Numeric;
    }
} // JsonStreamAnalyzer::Token
