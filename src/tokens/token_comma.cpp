#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token
{
    TokenComma::TokenComma(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    Type TokenComma::getType() {
        return Type::Comma;
    }
} // JsonStreamAnalyzer::Token
