#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token
{
    TokenNull::TokenNull(int line, int column) : Token(line, column, NULL) {
    }

    Type TokenNull::getType() {
        return Type::Null;
    }
} // JsonStreamAnalyzer::Token
