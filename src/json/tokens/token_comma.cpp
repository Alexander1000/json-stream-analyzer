#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer::Token {
    class TokenComma : public Token {
    public:
        TokenComma(int line, int column, IOReader *reader) : Token(line, column, reader) {
        }

        int getType() {
            return TOKEN_TYPE_COMMA;
        }
    };
}