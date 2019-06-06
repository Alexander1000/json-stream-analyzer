#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token
{
    TokenBool::TokenBool(int line, int column, bool value) : Token(line, column, NULL) {
        this->value = value;
    }

    Type TokenBool::getType() {
        return Type::Bool;
    }
} // JsonStreamAnalyzer::Token
