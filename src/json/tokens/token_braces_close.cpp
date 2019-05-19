#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer::Token {
    class TokenBracesClose : public Token {
    public:
        TokenBracesClose(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader) : Token(line, column, reader) {
        }

        int getType() {
            return TOKEN_TYPE_BRACES_CLOSE;
        }
    };
} // JsonStreamAnalyzer::Token
